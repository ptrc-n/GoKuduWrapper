/***********************************************************************
*  Licensed to the Apache Software Foundation (ASF) under one
*  or more contributor license agreements.  See the NOTICE file
*  distributed with this work for additional information
*  regarding copyright ownership.  The ASF licenses this file
*  to you under the Apache License, Version 2.0 (the
*  "License"); you may not use this file except in compliance
*  with the License.  You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
* limitations under the License.
***********************************************************************/

#pragma once
#include "stdbool.h"
#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

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
    
    typedef struct C_KuduStatus C_KuduStatus;
    typedef struct C_KuduInsert C_KuduInsert;
    typedef struct C_KuduPartialRow C_KuduPartialRow;
    typedef struct C_KuduSession C_KuduSession;
    typedef struct C_KuduScanBatch C_KuduScanBatch;
    typedef struct C_KuduScanner C_KuduScanner;
    typedef struct C_KuduPredicate C_KuduPredicate;
    typedef struct C_KuduValue C_KuduValue;
    typedef struct C_KuduTable C_KuduTable;
    typedef struct C_KuduColumnSpec C_KuduColumnSpec;
    typedef struct C_KuduSchemaBuilder C_KuduSchemaBuilder;
    typedef struct C_KuduSchema C_KuduSchema;
    typedef struct C_MonoDelta C_MonoDelta;
    typedef struct C_KuduTableCreator C_KuduTableCreator;
    typedef struct C_KuduClient C_KuduClient;
    typedef struct C_KuduClientBuilder C_KuduClientBuilder;
    
    // ********************************
    //          Status

    char* KuduStatus_Message(C_KuduStatus* self);
    void KuduStatus_Free(C_KuduStatus* self);
    

    // ********************************
    //          Insert

    void KuduInsert_Free(C_KuduInsert* self);
    C_KuduStatus* KuduInsert_SetBool(C_KuduInsert* ins, const char* col_name, bool val);
    C_KuduStatus* KuduInsert_SetInt16(C_KuduInsert* ins, const char* col_name, int16_t val);
    C_KuduStatus* KuduInsert_SetInt32(C_KuduInsert* ins, const char* col_name, int32_t val);
    C_KuduStatus* KuduInsert_SetInt64(C_KuduInsert* ins, const char* col_name, int64_t val);
    C_KuduStatus* KuduInsert_SetUnixTimeMicros(C_KuduInsert* ins, const char* col_name, int64_t val);
    C_KuduStatus* KuduInsert_SetFloat(C_KuduInsert* ins, const char* col_name, float val);
    C_KuduStatus* KuduInsert_SetDouble(C_KuduInsert* ins, const char* col_name, double val);


    // ********************************
    //          PartialRow
    
    void KuduPartialRow_Free(C_KuduPartialRow* self);
    C_KuduStatus* KuduPartialRow_SetBool(C_KuduPartialRow* ins, const char* col_name, bool val);
    C_KuduStatus* KuduPartialRow_SetInt16(C_KuduPartialRow* ins, const char* col_name, int16_t val);
    C_KuduStatus* KuduPartialRow_SetInt32(C_KuduPartialRow* ins, const char* col_name, int32_t val);
    C_KuduStatus* KuduPartialRow_SetInt64(C_KuduPartialRow* ins, const char* col_name, int64_t val);
    C_KuduStatus* KuduPartialRow_SetUnixTimeMicros(C_KuduPartialRow* ins, const char* col_name, int64_t val);
    C_KuduStatus* KuduPartialRow_SetFloat(C_KuduPartialRow* ins, const char* col_name, float val);
    C_KuduStatus* KuduPartialRow_SetDouble(C_KuduPartialRow* ins, const char* col_name, double val);


    // ********************************
    //          Session

    C_KuduStatus* KuduSession_Close(C_KuduSession* self);
    C_KuduStatus* KuduSession_SetFlushMode(C_KuduSession* self, C_FlushMode mode);
    C_KuduStatus* KuduSession_Apply(C_KuduSession* self, C_KuduInsert* ins);
    C_KuduStatus* KuduSession_Flush(C_KuduSession* self);


    // ********************************
    //          ScanBatch

    void KuduScanBatch_Free(C_KuduScanBatch* self);
    int KuduScanBatch_HasNext(C_KuduScanBatch* self);
    void KuduScanBatch_SeekNext(C_KuduScanBatch* self);
    const char* KuduScanBatch_Row_ToString(C_KuduScanBatch* self);


    // ********************************
    //          Scanner

    void KuduScanner_Free(C_KuduScanner* self);
    C_KuduStatus* KuduScanner_setProjectedColumnNames(C_KuduScanner* self, const char** col_names, int n_cols);
    C_KuduStatus* KuduScanner_Open(C_KuduScanner* self);
    int KuduScanner_HasMoreRows(C_KuduScanner* self);
    C_KuduStatus* KuduScanner_NextBatch(C_KuduScanner* self, C_KuduScanBatch* batch);


    // ********************************
    //          Predicate

    void KuduPredicate_Free(C_KuduPredicate* self);
    C_KuduPredicate* KuduPredicate_Clone(C_KuduPredicate* self);


    // ********************************
    //          Value
    
    void KuduValue_Free(C_KuduValue* self);
    C_KuduValue* KuduValue_FromInt64(int64_t value);
    C_KuduValue* KuduValue_FromFloat(float value);
    C_KuduValue* KuduValue_FromDouble(double value);
    C_KuduValue* KuduValue_FromBool(bool value);

    // ********************************
    //          Table

    void KuduTable_Close(C_KuduTable* self);
    C_KuduInsert* KuduTable_NewInsert(C_KuduTable* self);
    C_KuduScanner* KuduTable_NewScanner(C_KuduTable* self);
    C_KuduPredicate* KuduTable_NewComparisonPredicate(C_KuduTable* self,
                                                      const char* col_name,
                                                      C_ComparisonOp op,
                                                      C_KuduValue* value);


    // ********************************
    //          ColumnSpec

    void KuduColumnSpec_Free(C_KuduColumnSpec* self);
    C_KuduColumnSpec* KuduColumnSpec_Default(C_KuduColumnSpec* self, C_KuduValue* value);
    C_KuduColumnSpec* KuduColumnSpec_Compression(C_KuduColumnSpec* self, C_CompressionType compression);
    C_KuduColumnSpec* KuduColumnSpec_Encoding(C_KuduColumnSpec* self, C_EncodingType encoding);
    C_KuduColumnSpec* KuduColumnSpec_BlockSize(C_KuduColumnSpec* self, int32_t block_size);
    C_KuduColumnSpec* KuduColumnSpec_Comment(C_KuduColumnSpec* self, const char* comment);
    C_KuduColumnSpec* KuduColumnSpec_Precision(C_KuduColumnSpec* self, int8_t precision);
    C_KuduColumnSpec* KuduColumnSpec_Scale(C_KuduColumnSpec* self, int8_t scale);
    C_KuduColumnSpec* KuduColumnSpec_PrimaryKey(C_KuduColumnSpec* self);
    C_KuduColumnSpec* KuduColumnSpec_NotNull(C_KuduColumnSpec* self);
    C_KuduColumnSpec* KuduColumnSpec_Nullable(C_KuduColumnSpec* self);
    C_KuduColumnSpec* KuduColumnSpec_Type(C_KuduColumnSpec* self, C_DataType type);
    C_KuduColumnSpec* KuduColumnSpec_RemoveDefault(C_KuduColumnSpec* self);
    C_KuduColumnSpec* KuduColumnSpec_RenameTo(C_KuduColumnSpec* self, const char* new_name);


    // ********************************
    //          Schema

    C_KuduSchema* KuduSchema_Create();
    void KuduSchema_Free(C_KuduSchema* self);


    // ********************************
    //          SchemaBuilder

    C_KuduSchemaBuilder* KuduSchemaBuilder_Create();
    void KuduSchemaBuilder_Free(C_KuduSchemaBuilder* self);
    C_KuduColumnSpec* KuduSchemaBuilder_AddColumn(C_KuduSchemaBuilder* self, const char* name);
    C_KuduSchemaBuilder* KuduSchemaBuilder_SetPrimaryKey(C_KuduSchemaBuilder* self, const char** key_col_names, int32_t n_cols);
    C_KuduStatus* KuduSchemaBuilder_Build(C_KuduSchemaBuilder* self, C_KuduSchema* schema);


    // ********************************
    //          MonoTime

    void MonoDelta_Free(C_MonoDelta* self);
    C_MonoDelta* MonoDelta_FromSeconds(double seconds);
    C_MonoDelta* MonoDelta_FromMiliseconds(int64_t ms);
    C_MonoDelta* MonoDelta_FromMicroseconds(int64_t us);
    C_MonoDelta* MonoDelta_FromNanoseconds(int64_t ns);


    // ********************************
    //          TableCreator

    void KuduTableCreator_Free(C_KuduTableCreator* self);
    C_KuduTableCreator* KuduTableCreator_table_name(C_KuduTableCreator* self, const char* name);
    C_KuduTableCreator* KuduTableCreator_schema(C_KuduTableCreator* self, C_KuduSchema* schema);
    C_KuduTableCreator* KuduTableCreator_add_hash_partitions(C_KuduTableCreator* self,
                                                             const char** cols, 
                                                             int32_t n_cols,
                                                             int32_t n_buckets);
    C_KuduTableCreator* KuduTableCreator_add_hash_partitions_seed(C_KuduTableCreator* self,
                                                                  const char** cols, 
                                                                  int32_t n_cols,
                                                                  int32_t n_buckets,
                                                                  int32_t seed);
    C_KuduTableCreator* KuduTableCreator_set_range_partition_columns(C_KuduTableCreator* self,
                                                             const char** cols, 
                                                             int32_t n_cols);
    C_KuduTableCreator* KuduTableCreator_add_range_partition(C_KuduTableCreator* self,
                                                             C_KuduPartialRow* lower_bound,
                                                             C_KuduPartialRow* upper_bound,
                                                             C_RangePartitionBound lower_bound_type,
                                                             C_RangePartitionBound upper_bound_type);
    C_KuduTableCreator* KuduTableCreator_add_range_partition_split(C_KuduTableCreator* self, C_KuduPartialRow* split_row);
    C_KuduTableCreator* KuduTableCreator_num_replicas(C_KuduTableCreator* self, int32_t n_replicas);
    C_KuduTableCreator* KuduTableCreator_extra_configs(C_KuduTableCreator* self,
                                                       const char** keys,
                                                       const char** values,
                                                       int32_t len);
    C_KuduTableCreator* KuduTableCreator_timeout(C_KuduTableCreator* self, C_MonoDelta* timeout);
    C_KuduTableCreator* KuduTableCreator_wait(C_KuduTableCreator* self, bool wait);
    C_KuduStatus* KuduTableCreator_Create(C_KuduTableCreator* self);


    // ********************************
    //          Client

    C_KuduSession* KuduClient_NewSession(C_KuduClient* self);
    void KuduClient_Free(C_KuduClient* client);
    C_KuduTableCreator* KuduClient_NewTableCreator(C_KuduClient* self);
    C_KuduStatus* KuduClient_TableExists(C_KuduClient* self, const char* table_name, int* exists);
    C_KuduStatus* KuduClient_OpenTable(C_KuduClient* self, const char* table_name, C_KuduTable* table);

    // ToDo: Add Support for Authentication Credentials
    // ********************************
    //          ClientBuilder

    C_KuduClientBuilder* KuduClientBuilder_Create();
    void KuduClientBuilder_Free(C_KuduClientBuilder* self);
    void KuduClientBuilder_add_master_server_addr(C_KuduClientBuilder* self, const char* addr);
    void KuduClientBuilder_clear_master_server_addrs(C_KuduClientBuilder* self);
    C_KuduStatus* KuduClientBuilder_Build(C_KuduClientBuilder* self, C_KuduClient* client);

#ifdef __cplusplus
}
#endif