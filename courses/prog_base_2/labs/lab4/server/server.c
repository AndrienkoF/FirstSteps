#include <stdlib.h>

#include "../socket/socket.h"
#include "../leading/leading.h"
#include "server.h"
#include "../http/http.h"

static void server_notFound(socket_t* client);
static void server_send(socket_t* client, const char* smth);

static void server_homepage(socket_t* client){
    char homeBuf[10224];
    char *pageText = "<html><head><title>Homepage</title></head>"
                     "<body><h1>Hello!</h1>"
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

static char* server_getAllLeadingsJSON(leading_t** leadings){
    int count = leading_leadingsCount(leadings);
    char allOfTHem[2000] = "";
    for(int i = 0; i < MAX_LEADINGS; i++){
        if(leading_getId(leadings[i]) != -1)
            strcat(allOfTHem, leading_makeLeadingJSON(leadings[i]));
    }
    return allOfTHem;
}

static void server_sendLeadingsJSON(socket_t* client, leading_t** leadings){
    char homeBuf[10224];
    char pageText[1000];
    strcpy(pageText, server_getAllLeadingsJSON(leadings));
    sprintf(homeBuf,
            "HTTP/1.1 200 OK\n"
            "Content-Type: application/json\n"
            "Content-Length: %i\r\n\r\n"
            "\n%s", strlen(pageText)+1, pageText);

    socket_write_string(client, homeBuf);
    socket_close(client);
}

static char* server_getAllLeadingsHTML(leading_t** leadings){
    char allOfTHem[10000] = "";
    char one[1000];
    for(int i = 0; i < MAX_LEADINGS; i++){
        if(leading_getId(leadings[i]) != -1){
            sprintf(one,
                    "     <p>Id: %i<br>"
                    "     Name: <a href=\"/leadings/%i\">%s</a><br>"
                    "     <a href=\"/leadings/delete/%i\">Delete leading</a>"
                    "     <br><br></p>",
                    i, leading_getId(leadings[i]), leading_getName(leadings[i]),
                    leading_getId(leadings[i]));
            strcat(allOfTHem, one);
        }
    }
    strcat(allOfTHem, "<a href=\"/leadings/new/\">New leading</a>");
    return allOfTHem;
}

static void server_sendLeadingsHTML(socket_t* client, leading_t** leadings){
    char homeBuf[10224];
    char* pageText = server_getAllLeadingsHTML(leadings);
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

static void server_getByIdJSON(http_request_t request, socket_t* client, leading_t** leadings){
    int id;
    char* getId = strpbrk(request.uri, "0123456");
    if(getId){
        id = atoi(getId);
        if(id > 6 || id < 0 || leading_getId(leadings[id]) == -1){
            socket_write_string(client, "Wrong ID");
            return;
        }
    }else{
        server_notFound(client);
        return;
    }
    char buffer[1000] = "";
    char* leading = leading_makeLeadingJSON(leadings[id]);

    sprintf(buffer,
            "HTTP/1.1 200 OK\n"
            "Content-Type: application/json\n"
            "Content-Length: %i\r\n\r\n"
            "\n%s", strlen(leading)+1, leading);

    socket_write_string(client, buffer);
    socket_close(client);
}

static char* server_getLeadingHTML(leading_t* leading){
    char one[500] = "";
    sprintf(one,
            "        Id: %i<br>"
            "      Name: %s<br>"
            "   Surname: %s<br>"
            "Birth date: %s<br>"
            "Experience: %i<br>"
            "    Rating: %.2f<br><br>"
            "<p><a href=\"/leadings/delete/%i\">Delete</a></p>",
            leading_getId(leading), leading_getName(leading),
            leading_getSurname(leading), leading_getBirthdate(leading),
            leading_getExp(leading), leading_getRate(leading),
            leading_getId(leading));
    return one;
}

static void server_getByIdHTML(http_request_t request, socket_t* client, leading_t** leadings){
    int id;
    char* getId = strpbrk(request.uri, "0123456");
    if(getId){
        id = atoi(getId);
        if(id < 0 || id > 6 || leading_getId(leadings[id]) == -1){
            socket_write_string(client, "<h1>Wrong ID</h1><p><a href=\"/leadings/\">All leadings</a></p>");
            return;
        }
    }else{
        server_notFound(client);
        return;
    }
    char toSend[2000];
    char buffer[2000] = "<head><title>Leading</title></head><h1>Leading</h1><p><a href=\"/leadings/\">All leadings</a></p><p>";
    strcat(buffer, server_getLeadingHTML(leadings[id]));
    strcat(buffer, "</p>");

    sprintf(toSend,
            "HTTP/1.1 200 OK\n"
            "Content-Type: text/html\n"
            "Content-Length: %i\r\n\r\n"
            "\n%s", strlen(buffer), buffer);
    socket_write_string(client, toSend);
    socket_close(client);
}

static void server_deleteByIdHTML(http_request_t request, socket_t* client, leading_t** leadings){
    int id;
    char* getId = strpbrk(request.uri, "0123456");
    if(getId){
        id = atoi(getId);
        if(id < 0 || id > 6 || leading_getId(leadings[id]) == -1){
            socket_write_string(client, "<h1>Wrong ID</h1><p><a href=\"/leadings/\">All leadings</a></p>");
            return;
        }
    }else{
        server_notFound(client);
        return;
    }
    char toSend[2000];
    char buffer[2000];
    sprintf(buffer,
            "<head><title>Delete</title></head>"
            "<h1>Success</h1><p><a href=\"/leadings/\">All leadings</a></p>"
            "<p>Leading %s successfully deleted!</p>", leading_getName(leadings[id]));

    leading_fill(leadings[id], -1, "qqq", "qqq", "1111-11-11", 0, 0);

    sprintf(toSend,
            "HTTP/1.1 200 OK\n"
            "Content-Type: text/html\n"
            "Content-Length: %i\r\n\r\n"
            "\n%s", strlen(buffer), buffer);

    socket_write_string(client, toSend);
    socket_close(client);
}

static void server_deleteByIdJSON(http_request_t request, socket_t* client, leading_t** leadings){
    int id;
    char* getId = strpbrk(request.uri, "0123456");
    if(getId){
        id = atoi(getId);
        if(id<0 || id>6 || leading_getId(leadings[id]) == -1){
            socket_write_string(client, "<h1>Wrong ID</h1><p><a href=\"/leadings/\">All leadings</a></p>");
            return;
        }
    }else{
        server_notFound(client);
        return;
    }
    char toSend[2000];
    char buffer[2000];
    sprintf(buffer,
            "Success!"
            "Leading %s successfully deleted!", leading_getName(leadings[id]));

    leadings[id] = leading_new();

    sprintf(toSend,
            "HTTP/1.1 200 OK\n"
            "Content-Type: application/json\n"
            "Content-Length: %i\r\n\r\n"
            "\n%s", strlen(buffer), buffer);

    socket_write_string(client, toSend);
    socket_close(client);
}

static void server_postHTML(socket_t* client, leading_t** leadings){
    char buffer[2000] = "";
    int id = 0;
    int count = leading_leadingsCount(leadings);

    if(count >= MAX_LEADINGS){
        char fail[] = "<html><head><title>Failure</head></title>"
                     "<body><h1>Failure</h1>"
                     "<p>List is full!</p>"
                     "<p><a href=\"/leadings/\">Back to all leadings</a></p>"
                     "</body></html>";
        sprintf(buffer,
            "HTTP/1.1 200 OK\n"
            "Content-Type: text/html\n"
            "Content-Length: %i\r\n\r\n"
            "\n%s", strlen(fail), fail);

        socket_write_string(client, buffer);
        socket_close(client);
        return;
    }

    for(int i = 0; i<MAX_LEADINGS; i++, id++){
        if(leading_getId(leadings[i]) == -1)
            break;
    }

    char toSend[2000] = "";
    sprintf(toSend,
            "<html><head><title>Post</title></head>"
            "<body><h1>New leading</h1>"
            "<form action=\"/api/leadings/%i\" method=\"POST\">"
            "Name:<br><input type=\"text\" name=\"name\"><br>"
            "Surname:<br><input type=\"text\" name=\"surname\"><br>"
            "Birthday:<br><input type=\"text\" name=\"birthdate\"><br>"
            "Experience:<br><input type=\"text\" name=\"experience\"><br>"
            "Rating:<br><input type=\"text\" name=\"rating\"><br>"
            "<input type=\"submit\" value=\"Send POST request\" /></form><br>"
            "<p><a href=\"/leadings/\">Back to all leadings</a></p>"
            "</body></html>", id);
    sprintf(buffer,
            "HTTP/1.1 200 OK\n"
            "Content-Type: text/html\n"
            "Content-Length: %i\r\n\r\n"
            "\n%s", strlen(toSend), toSend);

    socket_write_string(client, buffer);
    socket_close(client);
}

static void server_post(http_request_t request, socket_t* client, leading_t** leadings){
    int id = 0;
    int count = leading_leadingsCount(leadings);
    char buffer[2000] ="";
    char* str;
    char* name = http_request_getArg(&request, "name");
    char* surname = http_request_getArg(&request, "surname");
    char* birthdate = http_request_getArg(&request, "birthdate");
    char* experience = http_request_getArg(&request, "experience");
    char* rating = http_request_getArg(&request, "rating");

    if(strlen(name) <= 1 || strlen(surname) <= 1 || strlen(birthdate) <= 1){
        server_send(client, "Name/Surname/Birthday wasn't filled in"
                            "<p><a href=\"/leadings/new/\">Back to POST</a></p>");
        return;
    }

    str = birthdate;

   if(strlen(birthdate) > 10 || str[4] != '-' || str[7] != '-' || isdigit(birthdate[0])==0 || isdigit(experience[0]) == 0 || isdigit(rating[0])==0){
        server_send(client, "Wrong data!"
                    "<p><a href=\"/leadings/new/\">Back to POST</a></p>");
        return;
    }

    if(experience == " ")
        experience = "0";

    if(rating == " ")
        rating = "0.0";

    if(count >= MAX_LEADINGS){
        char fail[] = "Limit of leadings!";
        sprintf(buffer,
            "HTTP/1.1 404 \n"
            "Content-Type: text\n"
            "Content-Length: %i\r\n\r\n"
            "\n%s", strlen(fail), fail);

        socket_write_string(client, buffer);
        socket_close(client);
        return;
    }

    for(int i = 0; i<MAX_LEADINGS; i++, id++)
    {
        if(leading_getId(leadings[i]) == -1)
            break;
    }

    int exp = atoi(experience);
    double rate = atof(rating);

    leading_fill(leadings[id], id, name, surname, birthdate, exp, rate);
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
    const char * pageText = "<h1>404</h1><p>Page Not Found!</p>";
    sprintf(homeBuf,
            "HTTP/1.1 404 \n"
            "Content-Type: text/html\n"
            "Content-Length: %i\n"
            "\n<h1>Error</h1><p>%s</p>", strlen(pageText), pageText);
    free(pageText);
    socket_write_string(client, homeBuf);
    socket_close(client);
}

void server_answerRequest(http_request_t request, socket_t* client, leading_t** leadings){
    puts(request.method);
    puts(request.uri);
    if(!strcmp(request.uri, "/")){
        server_homepage(client);
    }
    else if(!strcmp(request.uri, "/leadings") || !strcmp(request.uri, "/leadings/")){
        server_sendLeadingsHTML(client, leadings);
    }
    else if(strncmp(request.uri, "/api/leadings/", 13) == 0){
        if(!strcmp(request.method, "GET")){
            server_getByIdJSON(request, client, leadings);
        }
        else if(!strcmp(request.method, "DELETE")){
            server_deleteByIdJSON(request, client, leadings);
        }
        else if(!strcmp(request.method, "POST")){
            server_post(request, client, leadings);
        }
    }
    else if(!strcmp(request.uri, "/api/leadings") || !strcmp(request.uri, "/api/leadings/")){
        server_sendLeadingsJSON(client, leadings);
    }
    else if(!strcmp(request.uri, "/leadings/new/") || !strcmp(request.uri, "/leadings/new")){
        server_postHTML(client, leadings);
    }
    else if(strncmp(request.uri, "/leadings/delete/", 16) == 0){
        server_deleteByIdHTML(request, client, leadings);
    }
    else if(strncmp(request.uri, "/leadings/", 9) == 0){
        server_getByIdHTML(request, client, leadings);
    }

    else server_notFound(client);
}
