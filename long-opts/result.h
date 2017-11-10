#ifndef RESULT_H
#define RESULT_H

/*
** Type: result_t
** --------------
** Result Type for Getting Function Return Status
*/
typedef enum result
{
    /* General Results */
    RESULT_OK,                          /* Operation executed without errors   */
    RESULT_NOT_OK,                      /* Errors encountered during execution */

    /* Function Usage Errors */
    RESULT_ERROR_INCORRECT_ARGUMENT,    /* Incorrect function argument value */

    /* Options Parsing Errors */
    RESULT_ERROR_MISSING_OPTION_ARG,    /* Found option that has not required argument */
    RESULT_ERROR_UNSUPPORTED_OPTION,    /* Found option that is not suported           */
    RESULT_ERROR_UNRECOGNIZED_OPTION    /* Found option that can not be recognized     */
}
result_t;

#endif
