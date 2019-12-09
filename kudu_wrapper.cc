#include <kudu/client/client.h>
#include <kudu/util/status.h>
#include <kudu/client/write_op.h>
#include <kudu/client/value.h>
#include <kudu/client/schema.h>
#include <kudu/util/monotime.h>

#include "kudu_wrapper.h"

using kudu::client::KuduClientBuilder;
using kudu::client::KuduClient;
using kudu::client::KuduTable;
using kudu::client::KuduSchema;
using kudu::client::KuduSession;
using kudu::client::KuduColumnSchema;
using kudu::client::KuduSchemaBuilder;
using kudu::client::KuduTableCreator;
using kudu::Status;
using kudu::client::sp::shared_ptr;


namespace {
    std::vector<std::string> ArrayOfCStringToVec(const char** elems, int n_elems) {
        std::vector<std::string> local_v;
        local_v.reserve(n_elems);
        for (int i = 0; i < n_elems; i++) {
            local_v.push_back(std::string(elems[i]));
        }
        return local_v;
    }
}

extern "C" {

    // ********************************
    //          Convenience

    Status CreateClient(std::string master_server_addr, shared_ptr<KuduClient>* client) {
        return KuduClientBuilder()
            .master_server_addrs(std::vector<std::string>{master_server_addr})
            .Build(client);
    }

    // ********************************
    //          Status

    struct C_KuduStatus {
        shared_ptr<Status> status;
    };

    char* KuduStatus_Message(C_KuduStatus* self) {
        std::string msg = self->status->ToString();
        return strdup(msg.c_str());
    }

    void KuduStatus_Free(C_KuduStatus* self) {
        delete self;
    }

    C_KuduStatus* MakeStatus(Status s) {
        if (s.ok()) return nullptr;
        return new C_KuduStatus {shared_ptr<Status>(new Status(s))};
    }


    // ********************************
    //          Table

    C_KuduStatus* Kudu_DoesTableExist(const char* master_server_addr, 
                                      const char* table_name) {
        shared_ptr<KuduClient> client;
        Status s = CreateClient(
            std::string(master_server_addr), 
            &client
        );
        if (!s.ok()) {
            return MakeStatus(s);
        }
        shared_ptr<KuduTable> table;
        s = client->OpenTable(std::string(table_name), &table);
        return MakeStatus(s);
    }

    C_KuduStatus* Kudu_DeleteTable(const char* master_server_addr, 
                                   const char* table_name) {
        shared_ptr<KuduClient> client;
        Status s = CreateClient(
            std::string(master_server_addr),
            &client
        );
        if (!s.ok()) {
            return MakeStatus(s);
        }
        return MakeStatus(client->DeleteTable(std::string(table_name)));
    }

    C_KuduStatus* Kudu_CreateTable(const char* master_server_addr, const char* table_name,
                                   const char** col_names, C_DataType* type, int n_cols,
                                   int n_keys, const char** partition_cols, 
                                   int n_partitions, int n_buckets, int n_replicas) {
        shared_ptr<KuduClient> client;
        Status s = CreateClient(
            std::string(master_server_addr), 
            &client
        );
        if (!s.ok()) {
            return MakeStatus(s);
        }

        KuduSchema schema;
        KuduSchemaBuilder b;
        for (int i = 0; i < n_keys; i++) {
            b.AddColumn(std::string(col_names[i]))
                ->Type(static_cast<KuduColumnSchema::DataType>(type[i]))
                ->NotNull()->PrimaryKey();
        }
        for (int i = n_keys; i < n_cols; i++) {
            b.AddColumn(std::string(col_names[i]))
                ->Type(static_cast<KuduColumnSchema::DataType>(type[i]));
        }
        s = b.Build(&schema);
        if (!s.ok()) {
            return MakeStatus(s);
        }

        KuduTableCreator* table_creator = client->NewTableCreator();
        s = table_creator->table_name(std::string(table_name))
            .schema(&schema)
            .add_hash_partitions(ArrayOfCStringToVec(partition_cols, n_partitions), n_buckets)
            .num_replicas(n_replicas)
            .Create();
        delete table_creator;
        return MakeStatus(s);
    }

    C_KuduStatus* Kudu_InsertDataTestTable(const char* master_server_addr, 
                                           const char** names,
                                           int32_t* coins,
                                           int32_t nRows) {
        shared_ptr<KuduClient> client;
        Status s = CreateClient(
            std::string(master_server_addr), 
            &client
        );
        if (!s.ok()) {
            return MakeStatus(s);
        }

        shared_ptr<KuduTable> table;
        s = client->OpenTable("TestTable", &table);
        if (!s.ok()) {
            return MakeStatus(s);
        }

        shared_ptr<KuduSession> session = table->client()->NewSession();
        s = session->SetFlushMode(KuduSession::MANUAL_FLUSH);
        if (!s.ok()) {
            return MakeStatus(s);
        }

        for (int i = 0; i < nRows; i++) {
            auto insert = table->NewInsert();
            auto row = insert->mutable_row();
            row->SetString("name", std::string(names[i]));
            row->SetInt32("coins", coins[i]);
            s = session->Apply(insert);
            if (!s.ok()) {
                return MakeStatus(s);
            }
        }

        return MakeStatus(session->Flush());
    }

}