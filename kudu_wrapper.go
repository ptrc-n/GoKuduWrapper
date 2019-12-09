package gokudugo

// #cgo CXXFLAGS: --std=c++17 -w
// #cgo LDFLAGS: -L/usr/local/lib -lkudu_client
// #include "kudu_wrapper.h"
// #include <stdlib.h>
import "C"
import (
	"errors"
	"unsafe"
)

// Status which is returned by some operations
type Status C.C_KuduStatus

// CompressionType for columns
type CompressionType int

// CompressionType constants
const (
	DefaultCompression CompressionType = 0
	NoCompression      CompressionType = 1
	Snappy             CompressionType = 2
	LZ4                CompressionType = 3
	ZLib               CompressionType = 4
)

//EncodingType used for a column
type EncodingType int

//EncodingType constants for table columns
const (
	AutoEncoding   EncodingType = 0
	PlainEncoding  EncodingType = 1
	PrefixEncoding EncodingType = 2
	Rle            EncodingType = 4
	DictEncoding   EncodingType = 5
	BitShuffle     EncodingType = 6
	GroupVariant   EncodingType = 3
)

// DataType of a column
type DataType int

// DataTypes for Table Columns
const (
	Int8           DataType = 0
	Int16          DataType = 1
	Int32          DataType = 2
	Int64          DataType = 3
	String         DataType = 4
	Bool           DataType = 5
	Float          DataType = 6
	Double         DataType = 7
	Binary         DataType = 8
	UnixtimeMicros DataType = 9
	Decimal        DataType = 10
	Timestamp      DataType = UnixtimeMicros
)

// RangePartitionBound represents the bound of a range partition
type RangePartitionBound int

// RangePartitionBound constants
const (
	ExclusiveBound RangePartitionBound = 0
	InclusiveBound RangePartitionBound = 1
)

// *************************
//		Convenience

func statusToErr(status *C.C_KuduStatus) error {
	if status == nil {
		return nil
	}
	msg := C.KuduStatus_Message(status)
	defer C.free(unsafe.Pointer(msg))
	return errors.New(C.GoString(msg))
}

// ********************************
//          Table

// DoesTableExist with <tableName> managed by master server at <masterServerAddr>
func DoesTableExist(masterServerAddr string, tableName string) error {
	cMasterServerAddr := C.CString(masterServerAddr)
	defer C.free(unsafe.Pointer(cMasterServerAddr))
	cTableName := C.CString(tableName)
	defer C.free(unsafe.Pointer(cTableName))

	return statusToErr(C.Kudu_DoesTableExist(cMasterServerAddr, cTableName))
}

// CreateTableHashed managed by kudu master at <masterServerAddr>.
// <primaryKeyCols> specifies the number of primary key columns, 
// which must be the first <primaryKeyCols> columns
func CreateTableHashed(masterServerAddr string, tableName string,
	colNames []string, colTypes []DataType, primaryKeyCols int,
	partitionCols []string, nBuckets int32, nReplicas int32) error {

	cMasterServerAddr := C.CString(masterServerAddr)
	defer C.free(unsafe.Pointer(cMasterServerAddr))
	cTableName := C.CString(masterServerAddr)
	defer C.free(unsafe.Pointer(cTableName))

	cColNames := make([]*C.char, len(colNames))
	for i, name := range colNames {
		cColNames[i] = C.CString(name)
		defer C.free(unsafe.Pointer(cColNames[i]))
	}
	cPartitionCols := make([]*C.char, len(partitionCols))
	for i, name := range partitionCols {
		cPartitionCols[i] = C.CString(name)
		defer C.free(unsafe.Pointer(cPartitionCols[i]))
	}
	cDataTypes := make([]C.C_DataType, len(colTypes))
	for i, t := range colTypes {
		cDataTypes[i] = C.C_DataType(t)
		//defer C.free(unsafe.Pointer(&cDataTypes[i]))
	}

	return statusToErr(C.Kudu_CreateTable(
		cMasterServerAddr, cTableName,
		&cColNames[0], &cDataTypes[0], C.int(len(cColNames)),
		C.int(primaryKeyCols), &cPartitionCols[0], 
		C.int(len(cPartitionCols)), C.int(nBuckets), C.int(nReplicas)))
}
