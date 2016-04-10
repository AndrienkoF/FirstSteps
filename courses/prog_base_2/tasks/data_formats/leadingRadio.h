#ifndef LEADINGRADIO_H_INCLUDED
#define LEADINGRADIO_H_INCLUDED

typedef struct leading_s leading_t;
typedef struct work_s work_t;

leading_t * new_leading();
void leading_delete(leading_t * list);
void leading_downloadXML(leading_t ** list, const char * readXML);
void leading_printXML(leading_t * leading, int i);

#endif // LEADINGRADIO_H_INCLUDED
