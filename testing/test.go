package main

import (
	kudu "gokudugo"
	"fmt"
)

func main() {
	err := kudu.CreateTableHashed("127.0.0.1:7051", "TestTable",
		[]string{"name", "coins"}, []kudu.DataType{kudu.String, kudu.Int32},
		1, []string{"name"}, 5, 1)
	fmt.Println(err)
	err = kudu.DoesTableExist("127.0.0.1:7051", "TestTable")
	fmt.Println(err)
	err = kudu.DeleteTable("127.0.0.1:7051", "TestTable")
	fmt.Println(err)
}