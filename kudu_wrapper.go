// Package kuduWrapper wrapps the kudu c++ api
package kuduWrapper

import (
	"errors"
	"unsafe"
)

// #cgo CXXFLAGS: --std=c++17 -w
// #cgo LDFLAGS: -L/usr/local/lib -lkudu_client
// #include "mini-kudu-wrapper.h"
// #include <stdlib.h>
import "C"

// Status which is returned by some operations
type Status C.C_KuduStatus

// Insert represents a single which may be sent to the cluster
type Insert C.C_KuduInsert

// PartialRow which may contain values for a subset of the columns
type PartialRow C.C_KuduPartialRow

// Session of a kudu client
type Session C.C_KuduSession

// ScanBatch is a set of zero or more rows returned by a scan operation
type ScanBatch C.C_KuduScanBatch

// Scanner can be used to retrieve data from kudu
type Scanner C.C_KuduScanner

// Predicate for a kudu query
type Predicate C.C_KuduPredicate

// Value with a specific type for kudu columns
type Value C.C_KuduValue

// Table is just that, .. a table
type Table C.C_KuduTable

// ColumnSpec is an API for specifying or altering a column within a table schema
type ColumnSpec C.C_KuduColumnSpec

// SchemaBuilder is used for constructing schemas
type SchemaBuilder C.C_KuduSchemaBuilder

// Schema of a kudu table
type Schema C.C_KuduSchema

// MonoDelta is kudu's time interval representation
type MonoDelta C.C_MonoDelta

// TableCreator helps to create new tables with desired options
type TableCreator C.C_KuduTableCreator

// Client abstracts a connection to a kudu cluster
type Client C.C_KuduClient

// ClientBuilder helps to establish a connection to a kudu cluster
type ClientBuilder C.C_KuduClientBuilder

// FlushMode used for write operations
type FlushMode C.C_FlushMode

// ComparisonOp for comparision predicates which can be used for scanners
type ComparisonOp C.C_ComparisonOp

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

// *************************
//		Insert

// Free deletes the c-wrapper's 'Insert struct
// should be used to prevent memory leaks
func (i *Insert) Free() {
	C.KuduInsert_Free((*C.struct_C_KuduInsert)(i))
}

// SetBool for column 'colName'
func (i *Insert) SetBool(colName string, value bool) error {
	cColName := C.CString(colName)
	defer C.free(unsafe.Pointer(cColName))
	return statusToErr(C.KuduInsert_SetBool((*C.struct_C_KuduInsert)(i),
		cColName, C.bool(value)))
}

// SetInt16 for column 'colName'
func (i *Insert) SetInt16(colName string, value int16) error {
	cColName := C.CString(colName)
	defer C.free(unsafe.Pointer(cColName))
	return statusToErr(C.KuduInsert_SetInt16((*C.struct_C_KuduInsert)(i),
		cColName, C.short(value)))
}

// SetInt32 for column 'colName'
func (i *Insert) SetInt32(colName string, value int32) error {
	cColName := C.CString(colName)
	defer C.free(unsafe.Pointer(cColName))
	return statusToErr(C.KuduInsert_SetInt32((*C.struct_C_KuduInsert)(i),
		cColName, C.int(value)))
}

// SetInt64 for column 'colName'
func (i *Insert) SetInt64(colName string, value int64) error {
	cColName := C.CString(colName)
	defer C.free(unsafe.Pointer(cColName))
	return statusToErr(C.KuduInsert_SetInt64((*C.struct_C_KuduInsert)(i),
		cColName, C.long(value)))
}

// SetFloat for column 'colName'
func (i *Insert) SetFloat(colName string, value float32) error {
	cColName := C.CString(colName)
	defer C.free(unsafe.Pointer(cColName))
	return statusToErr(C.KuduInsert_SetFloat((*C.struct_C_KuduInsert)(i),
		cColName, C.float(value)))
}

// SetDouble for column 'colName'
func (i *Insert) SetDouble(colName string, value float64) error {
	cColName := C.CString(colName)
	defer C.free(unsafe.Pointer(cColName))
	return statusToErr(C.KuduInsert_SetDouble((*C.struct_C_KuduInsert)(i),
		cColName, C.double(value)))
}

// SetUnixTimeMicros for column 'colName'
func (i *Insert) SetUnixTimeMicros(colName string, value int64) error {
	cColName := C.CString(colName)
	defer C.free(unsafe.Pointer(cColName))
	return statusToErr(C.KuduInsert_SetUnixTimeMicros((*C.struct_C_KuduInsert)(i),
		cColName, C.long(value)))
}

// *************************
//		PartialRow

// Free deletes the c-wrapper's 'partialRow' struct
// should be used to prevent memory leaks
func (r *PartialRow) Free() {
	C.KuduPartialRow_Free((*C.struct_C_KuduPartialRow)(r))
}

// SetBool for column 'colName'
func (r *PartialRow) SetBool(colName string, value bool) error {
	cColName := C.CString(colName)
	defer C.free(unsafe.Pointer(cColName))
	return statusToErr(C.KuduPartialRow_SetBool((*C.struct_C_KuduPartialRow)(r),
		cColName, C.bool(value)))
}

// SetInt16 for column 'colName'
func (r *PartialRow) SetInt16(colName string, value int16) error {
	cColName := C.CString(colName)
	defer C.free(unsafe.Pointer(cColName))
	return statusToErr(C.KuduPartialRow_SetInt16((*C.struct_C_KuduPartialRow)(r),
		cColName, C.short(value)))
}

// SetInt32 for column 'colName'
func (r *PartialRow) SetInt32(colName string, value int32) error {
	cColName := C.CString(colName)
	defer C.free(unsafe.Pointer(cColName))
	return statusToErr(C.KuduPartialRow_SetInt32((*C.struct_C_KuduPartialRow)(r),
		cColName, C.int(value)))
}

// SetInt64 for column 'colName'
func (r *PartialRow) SetInt64(colName string, value int64) error {
	cColName := C.CString(colName)
	defer C.free(unsafe.Pointer(cColName))
	return statusToErr(C.KuduPartialRow_SetInt64((*C.struct_C_KuduPartialRow)(r),
		cColName, C.long(value)))
}

// SetFloat for column 'colName'
func (r *PartialRow) SetFloat(colName string, value float32) error {
	cColName := C.CString(colName)
	defer C.free(unsafe.Pointer(cColName))
	return statusToErr(C.KuduPartialRow_SetFloat((*C.struct_C_KuduPartialRow)(r),
		cColName, C.float(value)))
}

// SetDouble for column 'colName'
func (r *PartialRow) SetDouble(colName string, value float64) error {
	cColName := C.CString(colName)
	defer C.free(unsafe.Pointer(cColName))
	return statusToErr(C.KuduPartialRow_SetDouble((*C.struct_C_KuduPartialRow)(r),
		cColName, C.double(value)))
}

// SetUnixTimeMicros for column 'colName'
func (r *PartialRow) SetUnixTimeMicros(colName string, value int64) error {
	cColName := C.CString(colName)
	defer C.free(unsafe.Pointer(cColName))
	return statusToErr(C.KuduPartialRow_SetUnixTimeMicros((*C.struct_C_KuduPartialRow)(r),
		cColName, C.long(value)))
}

// *************************
//		Session

// Close the session
func (s *Session) Close() {
	statusToErr(C.KuduSession_Close((*C.struct_C_KuduSession)(s)))
}

// SetFlushMode for this session
// There should be no pending session when setting the flushmode,
// so 'Flush()' schould be called first.
func (s *Session) SetFlushMode(mode FlushMode) error {
	return statusToErr(C.KuduSession_SetFlushMode((*C.struct_C_KuduSession)(s),
		C.C_FlushMode(mode)))
}

// Apply the write operation to the Session
func (s *Session) Apply(ins *Insert) error {
	return statusToErr(C.KuduSession_Apply((*C.struct_C_KuduSession)(s),
		(*C.struct_C_KuduInsert)(ins)))
}

// Flush the current batch of buffered operations.
func (s *Session) Flush() error {
	return statusToErr(C.KuduSession_Flush((*C.struct_C_KuduSession)(s)))
}

// *************************
//		Scan Batch

// Free deletes the ScanBatch struct
// Should be called to prevent memory leaks
func (sb *ScanBatch) Free() {
	C.KuduScanBatch_Free((*C.struct_C_KuduScanBatch)(sb))
}

// HasNext inidicates whether there is another row in the batch
func (sb *ScanBatch) HasNext() bool {
	if C.KuduScanBatch_HasNext((*C.struct_C_KuduScanBatch)(sb)) == 0 {
		return false
	}
	return true
}

// SeekNext selects the next item in that batch
func (sb *ScanBatch) SeekNext() {
	C.KuduScanBatch_SeekNext((*C.struct_C_KuduScanBatch)(sb))
}

// RowToString returns the current row as string
func (sb *ScanBatch) RowToString() string {
	return C.GoString(C.KuduScanBatch_Row_ToString((*C.struct_C_KuduScanBatch)(sb)))
}

// *************************
//		Scanner

// Free deletes the Scanner struct
// Should be called to prevent memory leaks
func (s *Scanner) Free() {
	C.KuduScanner_Free((*C.struct_C_KuduScanner)(s))
}

// SetProjectedColumnNames the scanner using column names.
func (s *Scanner) SetProjectedColumnNames(colNames []string) error {
	cStrings := make([]*C.char, len(colNames))
	for i, name := range colNames {
		cStrings[i] = C.CString(name)
		defer C.free(unsafe.Pointer(cStrings[i]))
	}
	return statusToErr(C.KuduScanner_setProjectedColumnNames((*C.struct_C_KuduScanner)(s),
		&cStrings[0], C.int(len(colNames))))
}

// Open a scanner
func (s *Scanner) Open() error {
	return statusToErr(C.KuduScanner_Open((*C.struct_C_KuduScanner)(s)))
}

// HasMoreRows checks if there may be rows to be fetched from this scanner.
func (s *Scanner) HasMoreRows() bool {
	if C.KuduScanner_HasMoreRows((*C.struct_C_KuduScanner)(s)) == 0 {
		return false
	}
	return true
}

// NextBatch gets the next batch of rows.
func (s *Scanner) NextBatch(sb *ScanBatch) error {
	return statusToErr(C.KuduScanner_NextBatch((*C.struct_C_KuduScanner)(s),
		(*C.struct_C_KuduScanBatch)(sb)))
}

// *************************
//		Predicate

// Free deletes the c-wrappers 'predicate' struct
// should be used to prevent memory leaks
func (p *Predicate) Free() {
	C.KuduPredicate_Free((*C.struct_C_KuduPredicate)(p))
}

// Clone the predicate and return the copy
func (p *Predicate) Clone() *Predicate {
	return (*Predicate)(C.KuduPredicate_Clone((*C.struct_C_KuduPredicate)(p)))
}

// *************************
//		Value

// Free deletes the c-wrapper's 'kuduValue' struct
// use to prevent memory leaks
func (v *Value) Free() {
	C.KuduValue_Free((*C.struct_C_KuduValue)(v))
}

// ValueFromInt64 constructs a new Value from an integer
func ValueFromInt64(value int64) *Value {
	return (*Value)(C.KuduValue_FromInt64((C.long)(value)))
}

// ValueFromFloat consturcts a new Vlaue from float
func ValueFromFloat(value float32) *Value {
	return (*Value)(C.KuduValue_FromFloat((C.float)(value)))
}

// ValueFromDouble consturcts a new Vlaue from double
func ValueFromDouble(value float64) *Value {
	return (*Value)(C.KuduValue_FromDouble((C.double)(value)))
}

// ValueFromBool consturcts a new Vlaue from bool
func ValueFromBool(value bool) *Value {
	return (*Value)(C.KuduValue_FromBool((C.bool)(value)))
}

// *************************
//		Table

// Close deletes the c-wrapper's 'table' struct
// Use to prevent memory leaks
func (t *Table) Close() {
	C.KuduTable_Close((*C.struct_C_KuduTable)(t))
}

// NewInsert operaiton for that table
func (t *Table) NewInsert() *Insert {
	return (*Insert)(C.KuduTable_NewInsert((*C.struct_C_KuduTable)(t)))
}

// NewScanner for that table
func (t *Table) NewScanner() *Scanner {
	return (*Scanner)(C.KuduTable_NewScanner((*C.struct_C_KuduTable)(t)))
}

// NewComparisonPredicate for that table
func (t *Table) NewComparisonPredicate(colName string, op ComparisonOp, val *Value) *Predicate {
	cColName := C.CString(colName)
	defer C.free(unsafe.Pointer(cColName))
	return (*Predicate)(C.KuduTable_NewComparisonPredicate(
		(*C.struct_C_KuduTable)(t),
		cColName,
		C.C_ComparisonOp(op),
		(*C.struct_C_KuduValue)(val)))
}

// *************************
//		ColumnSpec

// Free deletes the c-wrapper's 'columnSpec' Object
// Use to prevent memory leaks
func (c *ColumnSpec) Free() {
	C.KuduColumnSpec_Free((*C.struct_C_KuduColumnSpec)(c))
}

// Default for that column
func (c *ColumnSpec) Default(value *Value) *ColumnSpec {
	c = (*ColumnSpec)(C.KuduColumnSpec_Default((*C.struct_C_KuduColumnSpec)(c),
		(*C.struct_C_KuduValue)(value)))
	return c
}

// Compression for that column
func (c *ColumnSpec) Compression(t CompressionType) *ColumnSpec {
	c = (*ColumnSpec)(C.KuduColumnSpec_Compression((*C.struct_C_KuduColumnSpec)(c),
		C.C_CompressionType(t)))
	return c
}

// Encoding for that column
func (c *ColumnSpec) Encoding(e EncodingType) *ColumnSpec {
	c = (*ColumnSpec)(C.KuduColumnSpec_Encoding((*C.struct_C_KuduColumnSpec)(c),
		C.C_EncodingType(e)))
	return c
}

// BlockSize for that column
func (c *ColumnSpec) BlockSize(bs int32) *ColumnSpec {
	c = (*ColumnSpec)(C.KuduColumnSpec_BlockSize((*C.struct_C_KuduColumnSpec)(c),
		C.int(bs)))
	return c
}

// Comment for that column
func (c *ColumnSpec) Comment(comment string) *ColumnSpec {
	cComment := C.CString(comment)
	defer C.free(unsafe.Pointer(cComment))
	c = (*ColumnSpec)(C.KuduColumnSpec_Comment((*C.struct_C_KuduColumnSpec)(c),
		cComment))
	return c
}

// Precision for that column must be between 1 and 38 and describes
// the number of digits used to represent the value
func (c *ColumnSpec) Precision(p int8) *ColumnSpec {
	c = (*ColumnSpec)(C.KuduColumnSpec_Precision((*C.struct_C_KuduColumnSpec)(c),
		(C.schar)(p)))
	return c
}

// Scale for that column must be between 0 and the columns precision and
// sets the number of digits after the decimal point
func (c *ColumnSpec) Scale(s int8) *ColumnSpec {
	c = (*ColumnSpec)(C.KuduColumnSpec_Scale((*C.struct_C_KuduColumnSpec)(c), C.schar(s)))
	return c
}

// PrimaryKey sets the column to be THE primary key of the table
// May only be used to set non-composite primary keys.
// To set composite primary keys use the SchemaBuilders SetPrimaryKey function
func (c *ColumnSpec) PrimaryKey() *ColumnSpec {
	c = (*ColumnSpec)(C.KuduColumnSpec_PrimaryKey((*C.struct_C_KuduColumnSpec)(c)))
	return c
}

// NotNull makes this column not-nullable
func (c *ColumnSpec) NotNull() *ColumnSpec {
	c = (*ColumnSpec)(C.KuduColumnSpec_NotNull((*C.struct_C_KuduColumnSpec)(c)))
	return c
}

// Type sets this columns DataType
func (c *ColumnSpec) Type(dt DataType) *ColumnSpec {
	c = (*ColumnSpec)(C.KuduColumnSpec_Type((*C.struct_C_KuduColumnSpec)(c), C.C_DataType(dt)))
	return c
}

// RemoveDefault is only relevant for alter table
// removes the default value for the column
func (c *ColumnSpec) RemoveDefault() *ColumnSpec {
	c = (*ColumnSpec)(C.KuduColumnSpec_RemoveDefault((*C.struct_C_KuduColumnSpec)(c)))
	return c
}

// RenameTo renames the column
func (c *ColumnSpec) RenameTo(newName string) *ColumnSpec {
	cName := C.CString(newName)
	defer C.free(unsafe.Pointer(cName))
	c = (*ColumnSpec)(C.KuduColumnSpec_RenameTo((*C.struct_C_KuduColumnSpec)(c), cName))
	return c
}

// *************************
//		Schema

// NewSchema instance that can be used for table creation or alteration
func NewSchema() *Schema {
	return (*Schema)(C.KuduSchema_Create())
}

// Free the c-wrapper's kudu schema instance
// should be used to prevent memory leaks
func (s *Schema) Free() {
	C.KuduSchema_Free((*C.struct_C_KuduSchema)(s))
}

// *************************
//		Schema Builder

// NewSchemaBuilder returns a SchemaBuilder instance
func NewSchemaBuilder() *SchemaBuilder {
	return (*SchemaBuilder)(C.KuduSchemaBuilder_Create())
}

// Free deletes the c-wrapper's 'schemaBuilder' struct
// should be used to prevent memory leaks
func (sb *SchemaBuilder) Free() {
	C.KuduSchemaBuilder_Free((*C.struct_C_KuduSchemaBuilder)(sb))
}

// AddColumn adds a new column with specified name to the schema
func (sb *SchemaBuilder) AddColumn(name string) *ColumnSpec {
	cName := C.CString(name)
	defer C.free(unsafe.Pointer(cName))
	return (*ColumnSpec)(C.KuduSchemaBuilder_AddColumn((*C.struct_C_KuduSchemaBuilder)(sb), cName))
}

// SetPrimaryKey may be used to specify compound primary keys.
func (sb *SchemaBuilder) SetPrimaryKey(keyColNames []string) *SchemaBuilder {
	var cKeyColNames []*C.char
	for _, name := range keyColNames {
		cKeyColNames = append(cKeyColNames, C.CString(name))
	}
	modifiedBuilder := C.KuduSchemaBuilder_SetPrimaryKey((*C.struct_C_KuduSchemaBuilder)(sb),
		&cKeyColNames[0],
		(C.int)(len(keyColNames)))
	for _, name := range cKeyColNames {
		C.free(unsafe.Pointer(name))
	}
	return (*SchemaBuilder)(modifiedBuilder)
}

// Build creates a Schema based on the SchemaBuilders current configuration
func (sb *SchemaBuilder) Build(schema *Schema) error {
	return statusToErr(C.KuduSchemaBuilder_Build((*C.struct_C_KuduSchemaBuilder)(sb),
		(*C.struct_C_KuduSchema)(schema)))
}

// *************************
//		MonoTime

// FreeMonoDelta deletes the C-wrappers struct
// Use to prevent memory leaks
func FreeMonoDelta(timedelta *MonoDelta) {
	C.MonoDelta_Free((*C.struct_C_MonoDelta)(timedelta))
}

// MonoDeltaFromSeconds converts seconds to kudus time interval representation
func MonoDeltaFromSeconds(seconds float64) *MonoDelta {
	return (*MonoDelta)(C.MonoDelta_FromSeconds((C.double)(seconds)))
}

// MonoDeltaFromMiliseconds converts miliseconds to kudus time interval representation
func MonoDeltaFromMiliseconds(ms int64) *MonoDelta {
	return (*MonoDelta)(C.MonoDelta_FromMiliseconds((C.long)(ms)))
}

// MonoDeltaFromMicroseconds converts microseconds to kudus time interval representation
func MonoDeltaFromMicroseconds(us int64) *MonoDelta {
	return (*MonoDelta)(C.MonoDelta_FromMicroseconds((C.long)(us)))
}

// MonoDeltaFromNanoseconds converts nanoseconds to kudus time interval representation
func MonoDeltaFromNanoseconds(ns int64) *MonoDelta {
	return (*MonoDelta)(C.MonoDelta_FromNanoseconds((C.long)(ns)))
}

// *************************
//		TableCreator

// Free deletes the C-wrappers struct
// Use to prevent memory leaks
func (tc *TableCreator) Free() {
	C.KuduTableCreator_Free((*C.struct_C_KuduTableCreator)(tc))
}

// TableName has to be called as a pre-condition for calling Create()
func (tc *TableCreator) TableName(name string) *TableCreator {
	cName := C.CString(name)
	defer C.free(unsafe.Pointer(cName))
	return (*TableCreator)(C.KuduTableCreator_table_name((*C.struct_C_KuduTableCreator)(tc), cName))
}

// Schema sets the schema with which to create the Table.
// Setting a scham is a pre-condition for calling Create()
func (tc *TableCreator) Schema(schema *Schema) *TableCreator {
	return (*TableCreator)(C.KuduTableCreator_schema((*C.struct_C_KuduTableCreator)(tc),
		(*C.struct_C_KuduSchema)(schema)))
}

// AddHashPartitions adds a set of hash partitions to the table
func (tc *TableCreator) AddHashPartitions(colNames []string, nBuckets int32) *TableCreator {
	cColNames := make([]*C.char, 0)
	for _, name := range colNames {
		cColNames = append(cColNames, C.CString(name))
	}
	modifiedCreator := C.KuduTableCreator_add_hash_partitions((*C.struct_C_KuduTableCreator)(tc),
		&cColNames[0],
		(C.int)(len(colNames)),
		(C.int)(nBuckets))
	for i := range cColNames {
		C.free(unsafe.Pointer(cColNames[i]))
	}
	return (*TableCreator)(modifiedCreator)
}

// AddHashPartitionsSeed adds a set of hash partitions to the table, using the seed value
// to randomize the mapping of rows to hash buckets
func (tc *TableCreator) AddHashPartitionsSeed(colNames []string, nBucktes int32, seed int32) *TableCreator {
	cColNames := make([]*C.char, 0)
	for _, name := range colNames {
		cColNames = append(cColNames, C.CString(name))
	}
	modifiedCreator := C.KuduTableCreator_add_hash_partitions_seed(
		(*C.struct_C_KuduTableCreator)(tc),
		&cColNames[0],
		(C.int)(len(colNames)),
		(C.int)(nBucktes),
		(C.int)(seed))
	for i := range cColNames {
		C.free(unsafe.Pointer(cColNames[i]))
	}
	return (*TableCreator)(modifiedCreator)
}

// AddRangePartition may add multiple range partitions, but they must not overlap.
// LowerBound and upperBound can be empty which imposes no lower or upper bound respectivly.
// Each splits that should be specified using AddRangePartitionSplit must fall in a RangePartition.
func (tc *TableCreator) AddRangePartition(lowerBound *PartialRow, upperBound *PartialRow,
	lowerBoundType RangePartitionBound, upperBoundType RangePartitionBound) *TableCreator {
	return (*TableCreator)(C.KuduTableCreator_add_range_partition(
		(*C.struct_C_KuduTableCreator)(tc),
		(*C.struct_C_KuduPartialRow)(lowerBound),
		(*C.struct_C_KuduPartialRow)(upperBound),
		C.C_RangePartitionBound(lowerBoundType),
		C.C_RangePartitionBound(upperBoundType)))
}

// AddRangePartitionSplit specifies a row which is to split a range partition in half.
// Each split must fall in a specified range partition.
func (tc *TableCreator) AddRangePartitionSplit(splitRow *PartialRow) *TableCreator {
	return (*TableCreator)(C.KuduTableCreator_add_range_partition_split((*C.struct_C_KuduTableCreator)(tc),
		(*C.struct_C_KuduPartialRow)(splitRow)))
}

func (tc *TableCreator) NumReplicas(nReplicas int) *TableCreator {
	return (*TableCreator)(C.KuduTableCreator_num_replicas((*C.struct_C_KuduTableCreator)(tc),
		(C.int)(nReplicas)))
}

// ExtraConfigs sets the table's extra configuration properties
// Eympty properties will be ignored
func (tc *TableCreator) ExtraConfigs(keys []string, values []string) *TableCreator {
	cKeys := make([]*C.char, 0)
	cValues := make([]*C.char, 0)
	for i, key := range keys {
		cKeys = append(cKeys, C.CString(key))
		cValues = append(cValues, C.CString(values[i]))
	}
	modifiedCreator := C.KuduTableCreator_extra_configs((*C.struct_C_KuduTableCreator)(tc),
		&cKeys[0],
		&cValues[0],
		(C.int)(len(keys)))
	for i := range cKeys {
		C.free(unsafe.Pointer(cKeys[i]))
		C.free(unsafe.Pointer(cValues[i]))
	}
	return (*TableCreator)(modifiedCreator)
}

// Timeout for table creation operation.
// Includes any waiting after create has been submitted.
func (tc *TableCreator) Timeout(timeout *MonoDelta) *TableCreator {
	return (*TableCreator)(C.KuduTableCreator_timeout((*C.struct_C_KuduTableCreator)(tc),
		(*C.struct_C_MonoDelta)(timeout)))
}

// Wait for the table to be created before returning
func (tc *TableCreator) Wait(wait bool) *TableCreator {
	return (*TableCreator)(C.KuduTableCreator_wait((*C.struct_C_KuduTableCreator)(tc), (C.bool)(wait)))
}

// Create a table in accordance with parameters currently set for the KuduTableCreator instance.
// Once created, the table can be obtained using the Client's OpenTable function.
func (tc *TableCreator) Create() error {
	return statusToErr(C.KuduTableCreator_Create((*C.struct_C_KuduTableCreator)(tc)))
}

// *************************
//		Client

// Close deletes the c-wrapper's 'client' struct
// should be used to prevent memory leaks
func (c *Client) Close() {
	C.KuduClient_Free((*C.struct_C_KuduClient)(c))
}

// NewSession for interacting with kudu.
func (c *Client) NewSession() *Session {
	return (*Session)(C.KuduClient_NewSession((*C.struct_C_KuduClient)(c)))
}

// NewTableCreator Object that can be used to add tables to kudu.
func (c *Client) NewTableCreator() *TableCreator {
	return (*TableCreator)(C.KuduClient_NewTableCreator((*C.struct_C_KuduClient)(c)))
}

// TableExists checks the existance of a table with the provided name
func (c *Client) TableExists(tableName string) (bool, error) {
	var exists int32 = -1
	cTableName := C.CString(tableName)
	defer C.free(unsafe.Pointer(cTableName))
	C.KuduClient_TableExists((*C.struct_C_KuduClient)(c), cTableName, (*C.int)(&exists))
	if exists == -1 {
		return false, errors.New("Could not determine wheter table exists")
	}
	if exists == 0 {
		return false, nil
	}
	return true, nil
}

// OpenTable <tableName> if it exists
func (c *Client) OpenTable(tableName string) (Table, error) {
	cTableName := C.CString(tableName)
	defer C.free(unsafe.Pointer(cTableName))
	localTable := new(Table)
	status := C.KuduClient_OpenTable(
		(*C.struct_C_KuduClient)(c),
		cTableName,
		(*C.struct_C_KuduTable)(localTable))
	e := statusToErr(status)
	return *localTable, e
}

// *************************
//		Client-Builder

// NewClientBuilder returns a ClientBuilder, which is a factory for creating clients
// that can be used to interact with kudu.
func NewClientBuilder() *ClientBuilder {
	return (*ClientBuilder)(C.KuduClientBuilder_Create())
}

// Free deltes the c-wrapper's 'client-builder' struct
// should be used to prevent memory leaks
func (b *ClientBuilder) Free() {
	C.KuduClientBuilder_Free((*C.struct_C_KuduClientBuilder)(b))
}

// AddMasterServerAddr adds an RPC address of a master to work with.
// At least one master server address is required for proper operation.
func (b *ClientBuilder) AddMasterServerAddr(addr string) {
	cAddr := C.CString(addr)
	defer C.free(unsafe.Pointer(cAddr))
	C.KuduClientBuilder_add_master_server_addr((*C.struct_C_KuduClientBuilder)(b), cAddr)
}

// ClearMasterServerAddrs to get rid of the current set of master addresses.
func (b *ClientBuilder) ClearMasterServerAddrs() {
	C.KuduClientBuilder_clear_master_server_addrs((*C.struct_C_KuduClientBuilder)(b))
}

// Build a client object that can be used to interact with kudu.
// Keep in mind that at least one master server RPC address is needed (AddMasterServerAddr).
func (b *ClientBuilder) Build() (Client, error) {
	client := new(Client)
	err := statusToErr(C.KuduClientBuilder_Build((*C.struct_C_KuduClientBuilder)(b),
		(*C.struct_C_KuduClient)(client)))
	if err != nil {
		return *client, err
	}
	return *client, nil
}
