#include <stdlib.h>
#include <stdbool.h>

#include "../socket/socket.h"
#include "../leading/leading.h"
#include "server.h"
#include "../database.h"
#include "../http/http.h"

static void server_notFound(socket_t* client);
static void server_send(socket_t* client, const char* smth);

static void server_homepage(socket_t* client){
    char homeBuf[10224];
    char *pageText = "<html><head><title>Homepage</title></head>"
                     "<body><h1>HELLO!</h1>"
                     "<p><a href=\"/leadings/\">All leadings</a></p>"
                     "</body></html>";
    sprintf(homeBuf,
            "HTTP/1.1 200 OK\n"
            "Content-Type: text/html\n"
            "Content-Length: %i\n"
            "Connection: keep-alive\n"
            "\n%s", strlen(pageText), pageText);

    socket_write_string(client, homeBuf);
    socket_close(client);
}

static char* server_getAllLeadingsJSON(db_t* base){
    char allOfTHem[4000] = "";
    int count = db_countLeadings(base);
    leading_t** leadings[count];

    for(int i = 0; i<count; i++)
        leadings[i] = leading_new();

    db_fillLeadingArr(base, leadings);

    for(int i = 0; i < count; i++){
        strcat(allOfTHem, leading_makeLeadingJSON(leadings[i]));
    }

    for(int i = 0; i<count; i++)
        leading_free(leadings[i]);

    return allOfTHem;
}

static void server_sendLeadingsJSON(socket_t* client, db_t* base){
    char homeBuf[10224];
    char pageText[5000];
    strcpy(pageText, server_getAllLeadingsJSON(base));
    sprintf(homeBuf,
            "HTTP/1.1 200 OK\n"
            "Content-Type: application/json\n"
            "Content-Length: %i\r\n\r\n"
            "\n%s", strlen(pageText)+1, pageText);

    socket_write_string(client, homeBuf);
    socket_close(client);
}

static char* server_getAllLeadingsHTML(db_t* base){
    char allOfTHem[10000] = "";
    char one[1000];
    int count = db_countLeadings(base);
    leading_t** leadings[count];
    for(int i = 0; i<count; i++)
        leadings[i] = leading_new();

    db_fillLeadingArr(base, leadings);

    for(int i = 0; i < count; i++){
        sprintf(one,
                "    <p>Id: %i<br>"
                "     Name: <a href=\"/leadings/%i\">%s</a><br>"
                "     <a href=\"/leadings/delete/%i\">Delete leading</a>"
                "     <br><br></p>",
                leading_getId(leadings[i]), leading_getId(leadings[i]), leading_getName(leadings[i]),
                leading_getId(leadings[i]));
        strcat(allOfTHem, one);
    }
    strcat(allOfTHem, "<a href=\"/leadings/new/\">New leading</a>");
    for(int i = 0; i<count; i++)
        leading_free(leadings[i]);
    return allOfTHem;
}

static void server_sendLeadingsHTML(socket_t* client, db_t* base){
    char homeBuf[10224];
    char* pageText = server_getAllLeadingsHTML(base);
    char request[2000] = "<head><title>Leadings</title></head><h1>Leadings</h1>";
    strcat(request, pageText);
    sprintf(homeBuf,
            "HTTP/1.1 200 OK\n"
            "Content-Type: text/html\n"
            "Content-Length: %i\n"
            "Connection: keep-alive\n"
            "\n%s", strlen(request), request);

    free(pageText);
    socket_write_string(client, homeBuf);
    socket_close(client);
}

static void server_getByIdJSON(http_request_t request, socket_t* client, db_t* base){
    int id;
    char* getId = strpbrk(request.uri, "0123456789");
    if(getId){
        id = atoi(getId);
        if(id <= 0 || !db_checkId(base, id)){
            socket_write_string(client, "Wrong ID");
            return;
        }
    }else{
        server_notFound(client);
        return;
    }
    char buffer[1000] = "";

    leading_t* leading = db_getLeadingById(base, id);
    char* leadingJSON = leading_makeLeadingJSON(leading);
    if(leadingJSON == NULL){
        socket_write_string(client, "Wrong ID");
        return;
    }

    sprintf(buffer,
            "HTTP/1.1 200 OK\n"
            "Content-Type: application/json\n"
            "Content-Length: %i\r\n\r\n"
            "\n%s", strlen(leadingJSON)+1, leadingJSON);

    socket_write_string(client, buffer);
    leading_free(leading);
    socket_close(client);
}

static char* server_getLeadingHTML(leading_t* leading){
    char one[500] = "";
    sprintf(one,
            "     Id: %i<br>"
            "   Name: %s<br>"
            "Surname: %s<br>"
            " Salary: %i<br>"
            "   Year: %i<br><br>"
            "<p><a href=\"/leadings/delete/%i\">Delete</a></p>",
            leading_getId(leading), leading_getName(leading),
            leading_getSurname(leading), leading_getSalary(leading),
            leading_getYear(leading), leading_getId(leading));
    return one;
}

static void server_getByIdHTML(http_request_t request, socket_t* client, db_t* base){
    int id;
    char* getId = strpbrk(request.uri, "0123456789");
    if(getId){
        id = atoi(getId);
        if(id <= 0 || !db_checkId(base, id)){
            socket_write_string(client, "<h1>Wrong ID</h1><p><a href=\"/leadings/\">All leadings</a></p>");
            return;
        }
    }else{
        server_notFound(client);
        return;
    }
    char toSend[2000];
    char buffer[2000] = "<head><title>Leading</title></head><h1>Leading</h1><p><a href=\"/leadings/\">All leadings</a></p><p>";
    leading_t* leading = db_getLeadingById(base, id);
    strcat(buffer, server_getLeadingHTML(leading));
    strcat(buffer, "</p>");

    sprintf(toSend,
            "HTTP/1.1 200 OK\n"
            "Content-Type: text/html\n"
            "Content-Length: %i\r\n\r\n"
            "\n%s", strlen(buffer), buffer);
    socket_write_string(client, toSend);
    leading_free(leading);
    socket_close(client);
}

static void server_deleteByIdHTML(http_request_t request, socket_t* client, db_t* base){
    int id;
    int count = db_countLeadings(base);
    char* getId = strpbrk(request.uri, "0123456789");
    if(getId){
        id = atoi(getId);
        if(id<=0 || !db_checkId(base, id)){
            socket_write_string(client, "<h1>Wrong ID</h1><p><a href=\"/leadings/\">All leadings</a></p>");
            return;
        }
    }else{
        server_notFound(client);
        return;
    }
    leading_t* leading = db_getLeadingById(base, id);
    char toSend[2000];
    char buffer[2000];
    sprintf(buffer,
            "<head><title>Delete</title></head>"
            "<h1>Success</h1><p><a href=\"/leadings/\">All leadings</a></p>"
            "<p>Leading %s successfully deleted!</p>", leading_getName(leading));

    db_deleteLeading(base, id);

    sprintf(toSend,
            "HTTP/1.1 200 OK\n"
            "Content-Type: text/html\n"
            "Content-Length: %i\r\n\r\n"
            "\n%s", strlen(buffer), buffer);

    socket_write_string(client, toSend);
    socket_close(client);
}

static void server_deleteByIdJSON(http_request_t request, socket_t* client, db_t* base){
    int id;
    char* getId = strpbrk(request.uri, "0123456789");
    if(getId){
        id = atoi(getId);
        if(id<=0 || !db_checkId(base, id))
        {
            socket_write_string(client, "{\nWrong ID\n}");
            return;
        }
    }else{
        server_notFound(client);
        return;
    }
    leading_t* leading = db_getLeadingById(base, id);
    char toSend[2000];
    char buffer[2000];
    sprintf(buffer,
            "Success!"
            "Leading %s successfully deleted!", leading_getName(leading));

    db_deleteLeading(base, id);

    sprintf(toSend,
            "HTTP/1.1 200 OK\n"
            "Content-Type: application/json\n"
            "Content-Length: %i\r\n\r\n"
            "\n%s", strlen(buffer), buffer);

    socket_write_string(client, toSend);
    socket_close(client);
}

static void server_postHTML(socket_t* client){
    char buffer[2000] = "";

    char toSend[2000] = "";
    strcpy(toSend,
            "<html><head><title>Post</title></head>"
            "<body><h1>New leading</h1>"
            "<form action=\"/api/leadings/\" method=\"POST\">"
            "Name:<br><input type=\"text\" name=\"name\"><br>"
            "Surname:<br><input type=\"text\" name=\"surname\"><br>"
            "Salary:<br><input type=\"text\" name=\"salary\"><br>"
            "Year:<br><input type=\"text\" name=\"year\"><br>"
            "<input type=\"submit\" value=\"Send POST request\" /></form><br>"
            "<p><a href=\"/leadings/\">Back to all leadings</a></p>"
            "</body></html>");
    sprintf(buffer,
            "HTTP/1.1 200 OK\n"
            "Content-Type: text/html\n"
            "Content-Length: %i\r\n\r\n"
            "\n%s", strlen(toSend), toSend);

    socket_write_string(client, buffer);
    socket_close(client);
}

static void server_post(http_request_t request, socket_t* client, db_t* base){
    char buffer[2000] ="";

    char* name = http_request_getArg(&request, "name");
    char* surname = http_request_getArg(&request, "surname");
    char* salary = http_request_getArg(&request, "salary");
    char* year = http_request_getArg(&request, "year");

    if(strlen(name) <= 1 || strlen(surname) <= 1){
        server_send(client, "Name/Surname wasn't filled in"
                            "<p><a href=\"/leadings/new/\">Back to POST</a></p>");
        return;
    }

   if(isdigit(salary[0]) == 0 || isdigit(year[0])==0){
        server_send(client, "Wrong data!"
                    "<p><a href=\"/leadings/new/\">Back to POST</a></p>");
        return;
    }

    if(salary == " ")
        salary = "0";

    if(year == " ")
        year = "0";

    leading_t* leading = leading_new();
    leading_fill(leading, -1, name, surname, atoi(salary), atoi(year));
    db_insertLeading(base, leading);
    leading_free(leading);
    server_send(client, "Success"
                "<p><a href=\"/leadings/\">All leadings</a></p>");

}

static void server_send(socket_t* client, const char* smth){
    char homeBuf[800];
    sprintf(homeBuf,
            "HTTP/1.1 200 OK\n"
            "Content-Type: text/html\n"
            "Content-Length: %i\n"
            "\n%s", strlen(smth), smth);
    socket_write_string(client, homeBuf);
    socket_close(client);
}

static void server_notFound(socket_t* client){
    char homeBuf[800];
    const char * pageText = "<h1>Error</h1><h2>404</h2><p>Page Not Found!</p>";
    sprintf(homeBuf,
            "HTTP/1.1 404 \n"
            "Content-Type: text/html\n"
            "Content-Length: %i\n"
            "\n%s", strlen(pageText), pageText);
    free(pageText);
    socket_write_string(client, homeBuf);
    socket_close(client);
}

static void server_personalTask(http_request_t request, socket_t* client, db_t* base){
    char salaryReq[10], salaryVal[10], yearReq[10], yearVal[10], toSend[10000];
    char* str = strtok(request.uri, "?&=");
    str = strtok(NULL, "?&=");
    strcpy(salaryReq, str); // salary_m || salary_l
    str = strtok(NULL, "?&=");
    strcpy(salaryVal, str); // salary value
    str = strtok(NULL, "?&=");
    strcpy(yearReq, str);   // year_m || year_l
    str = strtok(NULL, "?&=");
    strcpy(yearVal, str);   // year value
    int count = db_countLeadings(base);

    leading_t** leadings[count];
    for(int i = 0; i<count; i++)
        leadings[i] = leading_new();

    str = db_personalTask(base, salaryReq, atoi(salaryVal), yearReq, atoi(yearVal), leadings);

    sprintf(toSend,
            "HTTP/1.1 200 OK\n"
            "Content-Type: application/json\n"
            "Content-Length: %i\r\n\r\n"
            "\n%s", strlen(str)+1, str);

    for(int i = 0; i<count; i++)
        leading_free(leadings[i]);

    socket_write_string(client, toSend);
    socket_close(client);
}

void server_answerRequest(http_request_t request, socket_t* client, db_t* base){
    puts(request.method);
    puts(request.uri);
    if(!strcmp(request.uri, "/")){
        server_homepage(client);
    }
    else if(!strcmp(request.uri, "/leadings") || !strcmp(request.uri, "/leadings/")){
        server_sendLeadingsHTML(client, base);
    }
    else if(strncmp(request.uri, "/api/leadings/", 13) == 0){
        if(!strcmp(request.method, "POST")){
            server_post(request, client, base);
        }
        else if(!strcmp(request.method, "GET")){
            server_getByIdJSON(request, client, base);
        }
        else if(!strcmp(request.method, "DELETE")){
            server_deleteByIdJSON(request, client, base);
        }
    }
    if(!strcmp(request.uri, "/api/leadings") || !strcmp(request.uri, "/api/leadings/")){
        server_sendLeadingsJSON(client, base);
    }
    else if(strstr(request.uri, "/api/leadings/") == NULL && strstr(request.uri, "/api/leadings") != NULL){
        server_personalTask(request, client, base);
    }
    else if(!strcmp(request.uri, "/leadings/new/") || !strcmp(request.uri, "/leadings/new")){
        server_postHTML(client);
    }
    else if(strncmp(request.uri, "/leadings/delete/", 16) == 0){
        server_deleteByIdHTML(request, client, base);
    }
    else if(strncmp(request.uri, "/leadings/", 9) == 0){
        server_getByIdHTML(request, client, base);
    }

    else server_notFound(client);
}

