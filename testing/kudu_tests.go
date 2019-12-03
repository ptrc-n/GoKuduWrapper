package main

import (
	"fmt"

	kudu "kuduWrapper"
)

func main() {
	fmt.Println("Tests should follow now ... stay tuned!")
	kudu.CreateTable("TestTable", "localhost:7051", 1)
	kudu.TryOpenTable("TestTable", "localhost:7051")
}
