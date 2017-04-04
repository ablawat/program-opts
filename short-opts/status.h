#ifndef STATUS_H
#define STATUS_H

/* Available return statuses */
typedef enum status
{
    /* General */
    STATUS_OK,                          /* */
    STATUS_NOT_OK,                      /* */
    
    /* Input errors */
    STATUS_ERROR_INCORRECT_ARGUMENT,    /* */
    
    /* Parsing errors */
    STATUS_ERROR_MISSING_OPTION_ARG,    /* */
    STATUS_ERROR_UNSUPPORTED_OPTION,    /* */
    STATUS_ERROR_UNRECOGNIZED_OPTION    /* */
}
status_t;

#endif
