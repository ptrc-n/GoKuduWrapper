package main

import (
	kudu "gokudugo"
	"fmt"
	"time"
	"math/rand"
	"strconv"
)

func main() {
	fmt.Println(time.Now().String())
	err := kudu.CreateTableHashed("127.0.0.1:7051", "TestTable",
		[]string{"name", "coins"}, []kudu.DataType{kudu.String, kudu.Int32},
		1, []string{"name"}, 5, 1)
	fmt.Println(err)
	err = kudu.DoesTableExist("127.0.0.1:7051", "TestTable")
	fmt.Println(err)
	err = kudu.DeleteTable("127.0.0.1:7051", "TestTable")
	fmt.Println(err)

	fmt.Println(time.Now().String())
	fmt.Println("-->Generating rnd Datasets")
	names := make([]string, 25000)
	coins := make([]int, 25000)
	for i := range(names) {
		names[i] = strconv.Itoa(rand.Int())
		coins[i] = rand.Int()
	}
	
	fmt.Println("-->Starting Insert")
	fmt.Println(time.Now().String())
	kudu.InsertDataTestTable("127.0.0.1:7051", names, coins)
	fmt.Println("Finished!")
	fmt.Println(time.Now().String())
}