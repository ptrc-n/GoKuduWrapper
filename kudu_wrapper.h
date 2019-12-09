#pragma once
#include "stdbool.h"
#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif


    typedef struct C_KuduStatus C_KuduStatus;

    typedef enum {
        KUDU_AUTO_FLUSH_SYNC = 0,
        KUDU_AUTO_FLUSH_BACKGROUND = 1,
        KUDU_MANUAL_FLUSH = 2
    } C_FlushMode;

    typedef enum {
      LESS_EQUAL = 0,
      GREATER_EQUAL = 1,
      EQUAL = 2,
      LESS = 3,
      GREATER = 4
    } C_ComparisonOp;

    typedef enum {
        DEFAULT_COMPRESSION = 0,
        NO_COMPRESSION = 1,
        SNAPPY = 2,
        LZ4 = 3,
        ZLIB = 4
    } C_CompressionType;

    typedef enum {
        AUTO_ENCODING = 0,
        PLAIN_ENCODING = 1,
        PREFIX_ENCODING = 2,
        RLE = 4,
        DICT_ENCODING = 5,
        BIT_SHUFFLE = 6,
        GROUP_VARIANT = 3
    } C_EncodingType;

    typedef enum {
        INT8 = 0,
        INT16 = 1,
        INT32 = 2,
        INT64 = 3,
        STRING = 4,
        BOOL = 5,
        FLOAT = 6,
        DOUBLE = 7,
        BINARY = 8,
        UNIXTIME_MICROS = 9,
        DECIMAL = 10,
        TIMESTAMP = UNIXTIME_MICROS
    } C_DataType;

    typedef enum {
        EXCLUSIVE_BOUND,
        INCLUSIVE_BOUND
    } C_RangePartitionBound;
    
    // ********************************
    //          Status

    char* KuduStatus_Message(C_KuduStatus* self);
    void KuduStatus_Free(C_KuduStatus* self);
    
    // ********************************
    //          Table

    C_KuduStatus* Kudu_DoesTableExist(const char* master_server_add, 
                                      const char* table_name);
    C_KuduStatus* Kudu_DeleteTable(const char* master_server_addr, 
                                   const char* table_name);
    C_KuduStatus* Kudu_CreateTable(const char* master_server_addr, const char* table_name,
                                   const char** col_names, C_DataType* type, int n_cols,
                                   int n_keys, const char** partition_cols, 
                                   int n_partitions, int n_buckets, int n_replicas);
    C_KuduStatus* Kudu_InsertDataTestTable(const char* master_server_addr, 
                                           const char** names,
                                           int32_t* coins,
                                           int32_t nRows);
    C_KuduStatus* Kudu_CountData(const char* master_server_addr,
                                 const char* table_name,
                                 int* nRows);


#ifdef __cplusplus
}
#endif