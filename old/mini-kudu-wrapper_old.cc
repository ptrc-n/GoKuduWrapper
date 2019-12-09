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

#include <kudu/client/client.h>
#include <kudu/util/status.h>
#include <kudu/client/write_op.h>
#include <kudu/client/value.h>
#include <kudu/client/schema.h>
#include <kudu/util/monotime.h>

#include "mini-kudu-wrapper.h"

#include <vector>
#include <string>
#include <iostream>
#include <map>

#include <iostream>

using namespace kudu::client;
using namespace kudu;

namespace {
    template<class C1, class C2>
    std::vector<C1> FromCVector(const C2* c_elems, int len) {
        std::vector<C1> ret;
        ret.reserve(len);
        for (int i = 0; i < len; i++) {
            ret.emplace_back(c_elems[i]);
        }
        return ret;
    }

    std::vector<std::string> ArrayOfCStringToVec(const char** elems, int n_elems) {
        std::vector<std::string> local_v;
        local_v.reserve(n_elems);
        for (int i = 0; i < n_elems; i++) {
            local_v.push_back(std::string(elems[i]));
        }
        return local_v;
    }

    template<class C1, class C2>
    std::map<C1, C2> VectorsToMap(std::vector<C1> keys, std::vector<C2> values, int n_elems) {
        std::map<C1, C2> ret;
        for (int i = 0; i < n_elems; i++) {
            ret.insert(std::pair<C1, C2>(keys[i], values[i]));
        }
        return ret;
    }
}



extern "C" {

    // ********************************
    //          Status

    //ToDo: reslve incomplete type definitions and its dependencies
    struct C_KuduStatus {
        sp::shared_ptr<Status> status;
    };

    char* KuduStatus_Message(C_KuduStatus* self) {
        std::string msg = self->status->ToString();
        return strdup(msg.c_str());
    }

    void KuduStatus_Free(C_KuduStatus* self) {
        delete self;
    }

    static C_KuduStatus* MakeStatus(Status s) {
        if (s.ok()) return nullptr;
        return new C_KuduStatus {sp::shared_ptr<Status>(new Status(s))};
    }
    

    // ********************************
    //          Insert

    struct C_KuduInsert {
        sp::shared_ptr<KuduInsert> impl;
    };
    
    void KuduInsert_Free(C_KuduInsert* self) {
        delete self;
    }

    C_KuduStatus* KuduInsert_SetBool(C_KuduInsert* ins, 
                                    const char* col_name, 
                                    bool val) {
        auto cpp_ins = ins->impl;
        return MakeStatus(cpp_ins->mutable_row()->SetBool(col_name, val));
    }

    C_KuduStatus* KuduInsert_SetInt16(C_KuduInsert* ins,
                                    const char* col_name,
                                    int16_t val) {
        auto cpp_ins = ins->impl;
        return MakeStatus(cpp_ins->mutable_row()->SetInt16(col_name, val));
    }

    C_KuduStatus* KuduInsert_SetInt32(C_KuduInsert* ins,
                                        const char* col_name,
                                        int32_t val) {
        auto cpp_ins = ins->impl;
        return MakeStatus(cpp_ins->mutable_row()->SetInt32(col_name, val));
    }

    C_KuduStatus* KuduInsert_SetInt64(C_KuduInsert* ins,
                                        const char* col_name,
                                        int64_t val) {
        auto cpp_ins = ins->impl;
        return MakeStatus(cpp_ins->mutable_row()->SetInt64(col_name, val));
    }

    C_KuduStatus* KuduInsert_SetUnixTimeMicros(C_KuduInsert* ins,
                                        const char* col_name,
                                        int64_t val) {
        auto cpp_ins = ins->impl;
        return MakeStatus(cpp_ins->mutable_row()->SetUnixTimeMicros(col_name, val));
    }


    C_KuduStatus* KuduInsert_SetFloat(C_KuduInsert* ins,
                                        const char* col_name,
                                        float val) {
        auto cpp_ins = ins->impl;
        return MakeStatus(cpp_ins->mutable_row()->SetFloat(col_name, val));
    }


    C_KuduStatus* KuduInsert_SetDouble(C_KuduInsert* ins,
                                        const char* col_name,
                                        double val) {
        auto cpp_ins = ins->impl;
        return MakeStatus(cpp_ins->mutable_row()->SetDouble(col_name, val));
    }


    // ********************************
    //          Partial Row

    struct C_KuduPartialRow {
        sp::shared_ptr<KuduPartialRow> impl;
    };
    
    void KuduPartialRow_Free(C_KuduPartialRow* self) {
        delete self;
    }

    C_KuduStatus* KuduPartialRow_SetBool(C_KuduPartialRow* ins, 
                                    const char* col_name, 
                                    bool val) {
        auto cpp_ins = ins->impl;
        return MakeStatus(
            cpp_ins->SetBool(col_name, val)
        );
    }

    C_KuduStatus* KuduPartialRow_SetInt16(C_KuduPartialRow* ins,
                                    const char* col_name,
                                    int16_t val) {
        auto cpp_ins = ins->impl;
        return MakeStatus(
            cpp_ins->SetInt16(col_name, val)
        );
    }

    C_KuduStatus* KuduPartialRow_SetInt32(C_KuduPartialRow* ins,
                                        const char* col_name,
                                        int32_t val) {
        auto cpp_ins = ins->impl;
        return MakeStatus(
            cpp_ins->SetInt32(col_name, val)
        );
    }

    C_KuduStatus* KuduPartialRow_SetInt64(C_KuduPartialRow* ins,
                                        const char* col_name,
                                        int64_t val) {
        auto cpp_ins = ins->impl;
        return MakeStatus(
            cpp_ins->SetInt64(col_name, val)
        );
    }

    C_KuduStatus* KuduPartialRow_SetUnixTimeMicros(C_KuduPartialRow* ins,
                                        const char* col_name,
                                        int64_t val) {
        auto cpp_ins = ins->impl;
        return MakeStatus(
            cpp_ins->SetUnixTimeMicros(col_name, val)
        );
    }


    C_KuduStatus* KuduPartialRow_SetFloat(C_KuduPartialRow* ins,
                                        const char* col_name,
                                        float val) {
        auto cpp_ins = ins->impl;
        return MakeStatus(
            cpp_ins->SetFloat(col_name, val)
        );
    }


    C_KuduStatus* KuduPartialRow_SetDouble(C_KuduPartialRow* ins,
                                        const char* col_name,
                                        double val) {
        auto cpp_ins = ins->impl;
        return MakeStatus(
            cpp_ins->SetDouble(col_name, val)
        );
    }

    
    // ********************************
    //          Session

    struct C_KuduSession {
        sp::shared_ptr<KuduSession> impl;
    };

    C_KuduStatus* KuduSession_Close(C_KuduSession* self) {
        auto status = self->impl->Close();
        if (!status.ok()) {
            return MakeStatus(status);
        }
        delete self;
        return MakeStatus(status);
    }

    C_KuduStatus* KuduSession_SetFlushMode(C_KuduSession* self,
                                           C_FlushMode mode) {
        return MakeStatus(self->impl->SetFlushMode(static_cast<KuduSession::FlushMode>(mode)));
    }

    //ToDo: This function passes a raw pointer to Apply, which, according to documentation,
    // takes ownership of this pointer. This may lead to catastrophic behaviour.
    C_KuduStatus* KuduSession_Apply(C_KuduSession* self,
                                    C_KuduInsert* ins) {
        return MakeStatus(self->impl->Apply(
            reinterpret_cast<KuduWriteOperation*>(ins->impl.get())
        ));
    }

    C_KuduStatus* KuduSession_Flush(C_KuduSession* self) {
        return MakeStatus(self->impl->Flush());
    }


    // ********************************
    //          ScanBatch

    struct C_KuduScanBatch {
        KuduScanBatch impl;
        KuduScanBatch::RowPtr cur_row;
        int cur_idx = -1;
    };

    void KuduScanBatch_Free(C_KuduScanBatch* self) {
        delete self;
    }

    int KuduScanBatch_HasNext(C_KuduScanBatch* self) {
        return self->cur_idx + 1 < self->impl.NumRows();
    }

    void KuduScanBatch_SeekNext(C_KuduScanBatch* self) {
        self->cur_idx++;
        self->cur_row = self->impl.Row(self->cur_idx);
    }

    const char* KuduScanBatch_Row_ToString(C_KuduScanBatch* self) {
        return strdup(self->cur_row.ToString().c_str());
    }

    // ********************************
    //          Scanner

    struct C_KuduScanner {
        KuduScanner* impl;
    };

    void KuduScanner_Free(C_KuduScanner* self) {
        delete self;
    }

    C_KuduStatus* KuduScanner_setProjectedColumnNames(C_KuduScanner* self,
                                                  const char** col_names,
                                                  int n_cols) {
        return MakeStatus(self->impl->SetProjectedColumnNames(
            FromCVector<std::string>(col_names, n_cols))
        );
    }

    C_KuduStatus* KuduScanner_Open(C_KuduScanner* self) {
        return MakeStatus(self->impl->Open());
    }

    int KuduScanner_HasMoreRows(C_KuduScanner* self) {
        return self->impl->HasMoreRows();
    }

    C_KuduStatus* KuduScanner_NextBatch(C_KuduScanner* self,
                                        C_KuduScanBatch* batch) {
        return MakeStatus(self->impl->NextBatch(&batch->impl));
    }


    // ********************************
    //          Predicate

    struct C_KuduPredicate {
        KuduPredicate* impl;
    };

    void KuduPredicate_Free(C_KuduPredicate* self) {
        delete self;
    }

    C_KuduPredicate* KuduPredicate_Clone(C_KuduPredicate* self) {
        return std::move(new C_KuduPredicate{
            self->impl->Clone()
        });
    }



    // ********************************
    //          Value
    struct C_KuduValue {
        sp::shared_ptr<KuduValue> impl;
    };

    void KuduValue_Free(C_KuduValue* self) {
        delete self;
    }
    
    C_KuduValue* KuduValue_FromInt64(int64_t value) {
        return new C_KuduValue {
            sp::shared_ptr<KuduValue>(KuduValue::FromInt(value))
        };
    }

    C_KuduValue* KuduValue_FromFloat(float value) {
        return new C_KuduValue {
            sp::shared_ptr<KuduValue>(KuduValue::FromFloat(value))
        };
    }

    C_KuduValue* KuduValue_FromDouble(double value) {
        return new C_KuduValue {
            sp::shared_ptr<KuduValue>(KuduValue::FromDouble(value))
        };
    }

    C_KuduValue* KuduValue_FromBool(bool value) {
        return new C_KuduValue {
            sp::shared_ptr<KuduValue>(KuduValue::FromBool(value))
        };
    }


    // ********************************
    //          Table

    struct C_KuduTable {
        sp::shared_ptr<KuduTable> impl;
    };

    void KuduTable_Close(C_KuduTable* self) {
        delete self;
    }

    C_KuduInsert* KuduTable_NewInsert(C_KuduTable* self) {
        return new C_KuduInsert {
            sp::shared_ptr<KuduInsert>(self->impl->NewInsert())
        };
    } 
 
    C_KuduScanner* KuduTable_NewScanner(C_KuduTable* self) {
        return new C_KuduScanner { 
            std::move(new KuduScanner(self->impl.get()))
        };
    } 
 
    C_KuduPredicate* KuduTable_NewComparisonPredicate(C_KuduTable* self,
                                                      const char* col_name,
                                                      C_ComparisonOp op,
                                                      C_KuduValue* value) {
        auto cpp_op = reinterpret_cast<KuduPredicate::ComparisonOp*>(op);
        auto cpp_val = reinterpret_cast<KuduValue*>(value);
        return new C_KuduPredicate {
                self->impl->NewComparisonPredicate(col_name, *cpp_op, cpp_val)
        };
    }


    // ********************************
    //          ColumnSpec

    struct C_KuduColumnSpec {
        KuduColumnSpec* impl;
    };

    void KuduColumnSpec_Free(C_KuduColumnSpec* self) {
        delete self;
    }

    C_KuduColumnSpec* KuduColumnSpec_Default(C_KuduColumnSpec* self,
                                             C_KuduValue* value) {
        KuduColumnSpec* modifiedSpec = self->impl->Default(reinterpret_cast<KuduValue*>(value));
        return new C_KuduColumnSpec{modifiedSpec};
    }

    C_KuduColumnSpec* KuduColumnSpec_Compression(C_KuduColumnSpec* self,
                                                 C_CompressionType compression) {
        KuduColumnSpec* modified = self->impl->Compression(
                static_cast<KuduColumnStorageAttributes::CompressionType>(compression)
        );
        return new C_KuduColumnSpec{modified};
    }

    C_KuduColumnSpec* KuduColumnSpec_Encoding(C_KuduColumnSpec* self,
                                              C_EncodingType encoding) {
        KuduColumnSpec* modified = self->impl->Encoding(
            static_cast<KuduColumnStorageAttributes::EncodingType>(encoding)
        );
        return new C_KuduColumnSpec{ modified };
    }

    C_KuduColumnSpec* KuduColumnSpec_BlockSize(C_KuduColumnSpec* self,
                                               int32_t block_size) {
        KuduColumnSpec* modified = self->impl->BlockSize(block_size);
        return new C_KuduColumnSpec { modified };
    }

    C_KuduColumnSpec* KuduColumnSpec_Comment(C_KuduColumnSpec* self,
                                             const char* comment) {
        KuduColumnSpec* modified = self->impl->Comment(comment);
        return new C_KuduColumnSpec { modified };
    }

    C_KuduColumnSpec* KuduColumnSpec_Precision(C_KuduColumnSpec* self,
                                               int8_t precision) {
        KuduColumnSpec* modified = self->impl->Precision(precision);
        return new C_KuduColumnSpec { modified };
    }

    C_KuduColumnSpec* KuduColumnSpec_Scale(C_KuduColumnSpec* self,
                                               int8_t scale) {
        KuduColumnSpec* modified = self->impl->Scale(scale);
        return new C_KuduColumnSpec { modified };
    }

    C_KuduColumnSpec* KuduColumnSpec_PrimaryKey(C_KuduColumnSpec* self) {
        KuduColumnSpec* modified = self->impl->PrimaryKey();
        return new C_KuduColumnSpec { modified };
    }

    C_KuduColumnSpec* KuduColumnSpec_NotNull(C_KuduColumnSpec* self) {
        KuduColumnSpec* modified = self->impl->NotNull();
        return new C_KuduColumnSpec { modified };
    }

    C_KuduColumnSpec* KuduColumnSpec_Nullable(C_KuduColumnSpec* self) {
        KuduColumnSpec* modified = self->impl->Nullable();
        return new C_KuduColumnSpec { modified };
    }

    C_KuduColumnSpec* KuduColumnSpec_Type(C_KuduColumnSpec* self,
                                          C_DataType type) {
        KuduColumnSpec* modified = self->impl->Type(
            static_cast<KuduColumnSchema::DataType>(type)
        );
        return new C_KuduColumnSpec { modified };
    }

    C_KuduColumnSpec* KuduColumnSpec_RemoveDefault(C_KuduColumnSpec* self) {
        KuduColumnSpec* modified = self->impl->RemoveDefault();
        return new C_KuduColumnSpec { modified };
    }

    C_KuduColumnSpec* KuduColumnSpec_RenameTo(C_KuduColumnSpec* self,
                                              const char* new_name) {
        KuduColumnSpec* modified = self->impl->RenameTo(new_name);
        return new C_KuduColumnSpec { modified };
    }

    // ********************************
    //          Schema

    struct C_KuduSchema {
        sp::shared_ptr<KuduSchema> impl;
    };

    C_KuduSchema* KuduSchema_Create() {
        return new C_KuduSchema {
            sp::shared_ptr<KuduSchema>(new KuduSchema())
        };
    }

    void KuduSchema_Free(C_KuduSchema* self) {
        delete self;
    }


    // ********************************
    //          SchemaBuilder

    struct C_KuduSchemaBuilder {
        sp::shared_ptr<KuduSchemaBuilder> impl;
    };

    C_KuduSchemaBuilder* KuduSchemaBuilder_Create() {
        return new C_KuduSchemaBuilder { 
            sp::shared_ptr<KuduSchemaBuilder>(new KuduSchemaBuilder())
        };
    }

    void KuduSchemaBuilder_Free(C_KuduSchemaBuilder* self) {
        delete self;
    }

    C_KuduColumnSpec* KuduSchemaBuilder_AddColumn(C_KuduSchemaBuilder* self, 
                                                  const char* name) {
        return new C_KuduColumnSpec{ self->impl->AddColumn(name) };
    }

    C_KuduSchemaBuilder* KuduSchemaBuilder_SetPrimaryKey(C_KuduSchemaBuilder* self,
                                                         const char** key_col_names,
                                                         int32_t n_cols) {
        auto cpp_key_col_names = FromCVector<std::string>(key_col_names, n_cols);
        self->impl = sp::shared_ptr<KuduSchemaBuilder>(
            self->impl->SetPrimaryKey(cpp_key_col_names)
        );
        return self;
    }

    C_KuduStatus* KuduSchemaBuilder_Build(C_KuduSchemaBuilder* self,
                                         C_KuduSchema* schema) {
        return MakeStatus(
            self->impl->Build(schema->impl.get())
        );
    }


    // ********************************
    //          MonoTime

    struct C_MonoDelta {
        sp::shared_ptr<MonoDelta> impl;
    };

    void MonoDelta_Free(C_MonoDelta* self) {
        delete self;
    }

    C_MonoDelta* MonoDelta_FromSeconds(double seconds) {
        MonoDelta delta = MonoDelta::FromSeconds(seconds);
        return new C_MonoDelta { 
            sp::shared_ptr<MonoDelta>(&delta) 
        };
    }

    C_MonoDelta* MonoDelta_FromMiliseconds(int64_t ms) {
        MonoDelta delta = MonoDelta::FromMilliseconds(ms);
        return new C_MonoDelta { 
            sp::shared_ptr<MonoDelta>(&delta)
        };
    }

    C_MonoDelta* MonoDelta_FromMicroseconds(int64_t us) {
        MonoDelta delta = MonoDelta::FromMicroseconds(us);
        return new C_MonoDelta { 
            sp::shared_ptr<MonoDelta>(&delta)
        };
    }

    C_MonoDelta* MonoDelta_FromNanoseconds(int64_t ns) {
        MonoDelta delta = MonoDelta::FromNanoseconds(ns);
        return new C_MonoDelta { 
            sp::shared_ptr<MonoDelta>(&delta)
        };
    }

    // ********************************
    //          TableCreator

   struct C_KuduTableCreator {
        sp::shared_ptr<KuduTableCreator> impl;
        sp::shared_ptr<KuduSchema> schema;
    };

    void KuduTableCreator_Free(C_KuduTableCreator* self) {
        delete self;
    }

    C_KuduTableCreator* KuduTableCreator_table_name(C_KuduTableCreator* self,
                                                    const char* name) {
        self->impl->table_name(std::string(strdup(name)));
        return self;
    }

    C_KuduTableCreator* KuduTableCreator_schema(C_KuduTableCreator* self,
                                                C_KuduSchema* schema) {
        self->schema = sp::shared_ptr<KuduSchema>(new KuduSchema(*schema->impl));
        self->impl->schema(self->schema.get());
        return self;
    }

    C_KuduTableCreator* KuduTableCreator_add_hash_partitions(C_KuduTableCreator* self,
                                                             const char** cols, 
                                                             int32_t n_cols,
                                                             int32_t n_buckets) {
        self->impl->add_hash_partitions(ArrayOfCStringToVec(cols, n_cols), n_buckets);
        return self;
    }

    C_KuduTableCreator* KuduTableCreator_add_hash_partitions_seed(C_KuduTableCreator* self,
                                                                  const char** cols, 
                                                                  int32_t n_cols,
                                                                  int32_t n_buckets,
                                                                  int32_t seed) {
        self->impl->add_hash_partitions(ArrayOfCStringToVec(cols, n_cols), n_buckets, seed);
        return self;
    }

    C_KuduTableCreator* KuduTableCreator_set_range_partition_columns(C_KuduTableCreator* self,
                                                             const char** cols, 
                                                             int32_t n_cols) {
        self->impl->set_range_partition_columns(ArrayOfCStringToVec(cols, n_cols));
        return self;
    }

    C_KuduTableCreator* KuduTableCreator_add_range_partition(C_KuduTableCreator* self,
                                                             C_KuduPartialRow* lower_bound,
                                                             C_KuduPartialRow* upper_bound,
                                                             C_RangePartitionBound lower_bound_type = INCLUSIVE_BOUND,
                                                             C_RangePartitionBound upper_bound_type = EXCLUSIVE_BOUND) {
        self->impl->add_range_partition(
            reinterpret_cast<KuduPartialRow*>(lower_bound),
            reinterpret_cast<KuduPartialRow*>(upper_bound),
            static_cast<KuduTableCreator::RangePartitionBound>(lower_bound_type),
            static_cast<KuduTableCreator::RangePartitionBound>(upper_bound_type)
        );
        return self;
    }

    C_KuduTableCreator* KuduTableCreator_add_range_partition_split(C_KuduTableCreator* self,
                                                                   C_KuduPartialRow* split_row) {
        
        self->impl->add_range_partition_split(reinterpret_cast<KuduPartialRow*>(split_row));
        return self;
    }

    C_KuduTableCreator* KuduTableCreator_num_replicas(C_KuduTableCreator* self,
                                                      int32_t n_replicas) {
        self->impl->num_replicas(n_replicas);
        return self;
    }

   C_KuduTableCreator* KuduTableCreator_extra_configs(C_KuduTableCreator* self,
                                                       const char** keys,
                                                       const char** values,
                                                       int32_t len) {
        std::vector<std::string> local_keys = ArrayOfCStringToVec(keys, len);
        std::vector<std::string> local_values = ArrayOfCStringToVec(values, len);
        self->impl->extra_configs(VectorsToMap<std::string, std::string>(local_keys, local_values, len));
        return self;
    }

    C_KuduTableCreator* KuduTableCreator_timeout(C_KuduTableCreator* self,
                                                 C_MonoDelta* timeout) {
        self->impl->timeout(*timeout->impl);
        return self;
    }

    C_KuduTableCreator* KuduTableCreator_wait(C_KuduTableCreator* self,
                                              bool wait) {
        self->impl->wait(wait);
        return self;
    }

    C_KuduStatus* KuduTableCreator_Create(C_KuduTableCreator* self) {
        return MakeStatus(self->impl->Create());
    }


    // ********************************
    //          Client

    struct C_KuduClient {
        sp::shared_ptr<KuduClient> impl;
    };

    C_KuduSession* KuduClient_NewSession(C_KuduClient* self) {
        return new C_KuduSession {self->impl->NewSession()};
    }

    void KuduClient_Free(C_KuduClient* client) {
        delete client;
    }

    C_KuduTableCreator* KuduClient_NewTableCreator(C_KuduClient* self) {
        return new C_KuduTableCreator { 
            sp::shared_ptr<KuduTableCreator>(self->impl->NewTableCreator())
        };
    }

    C_KuduStatus* KuduClient_TableExists(C_KuduClient* self,
                                         const char* table_name,
                                         int* exists) {
        bool exists_b;
        Status s = self->impl->TableExists(std::string(table_name), &exists_b);
        if (!s.ok()) return MakeStatus(std::move(s));
        *exists = exists_b;
        return nullptr;
    }

    C_KuduStatus* KuduClient_OpenTable(C_KuduClient* self,
                                       const char* table_name,
                                       C_KuduTable* table) {
        return MakeStatus (
            self->impl->OpenTable(std::string(table_name), &table->impl)
        );
    }


    // ToDo: Add Support for Authentication Credentials
    // ********************************
    //          ClientBuilder

    struct C_KuduClientBuilder {
        sp::shared_ptr<KuduClientBuilder> impl;
    };

    C_KuduClientBuilder* KuduClientBuilder_Create() {
        auto ret = new C_KuduClientBuilder();
        ret->impl = sp::shared_ptr<KuduClientBuilder>(new KuduClientBuilder());
        return ret;
    }

    void KuduClientBuilder_Free(C_KuduClientBuilder* self) {
        delete self;
    }

    void KuduClientBuilder_add_master_server_addr(C_KuduClientBuilder* self, const char* addr) {
        self->impl->add_master_server_addr(std::string(addr));
    }

    void KuduClientBuilder_clear_master_server_addrs(C_KuduClientBuilder* self) {
        self->impl->clear_master_server_addrs();
    }

    C_KuduStatus* KuduClientBuilder_Build(C_KuduClientBuilder* self,
                                          C_KuduClient* client) {
        return MakeStatus(
            self->impl->Build(&client->impl)
        );
    }

}