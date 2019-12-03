// Package kuduWrapper wrapps the kudu c++ api
package kuduWrapper

import (
	"fmt"
)

// CreateTable with given tableName at specified masterServer
func CreateTable(tableName string, masterServer string, nReplicas int) {
	clientBuilder := NewClientBuilder()
	clientBuilder.AddMasterServerAddr(masterServer)
	defer clientBuilder.Free()

	client, err := clientBuilder.Build()
	if err != nil {
		fmt.Printf("ClientBuilder returned %v \n", err)
		return
	}
	// defer client.Close()

	schema := NewSchema()
	schemaBuilder := NewSchemaBuilder()
	schemaBuilder.AddColumn("name").Type(String).NotNull().PrimaryKey()
	schemaBuilder.AddColumn("credits").Type(Int32)
	err = schemaBuilder.Build(schema)
	if err != nil {
		fmt.Printf("SchemaBuilder returned %v \n", err)
		return
	}

	tableCreator := client.NewTableCreator()
	defer tableCreator.Free()
	tableCreator = tableCreator.TableName(tableName).Schema(schema).AddHashPartitions([]string{"name"}, 4)
	err = tableCreator.NumReplicas(nReplicas).Create()
	if err != nil {
		fmt.Printf("TableCreator returned %v \n", err)
		return
	}
}

// TryOpenTable with name 'tableName' managed by 'masterServer'
func TryOpenTable(tableName string, masterServer string) {
	clientBuilder := NewClientBuilder()
	clientBuilder.AddMasterServerAddr(masterServer)
	defer clientBuilder.Free()

	client, err := clientBuilder.Build()
	if err != nil {
		fmt.Printf("ClientBuilder returned %v \n", err)
		return
	}
	//defer client.Close()

	_, err = client.OpenTable(tableName)
	if err != nil {
		fmt.Println("Could not open Table")
		return
	}
	//defer table.Close()
	fmt.Println("Sucessfully opended Table")
}
