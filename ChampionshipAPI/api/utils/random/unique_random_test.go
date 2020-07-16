package random

import (
	"reflect"
	"testing"
)

// TestShuffleUint64  test shuffle uint64 slice
func TestShuffleUint64(t *testing.T) {
	var testSlice = []uint64{1, 2, 3, 4, 5, 6, 7, 8, 9}
	var correctSlice1 = []uint64{1, 2, 3, 4, 5, 6, 7, 8, 9}
	var correctSlice2 = []uint64{1, 2, 3, 4, 5, 6, 7, 8, 9}

	ShuffleUint64(&testSlice)

	if reflect.DeepEqual(testSlice, correctSlice1) {
		t.Fatalf("shuffling doesnt work! \n test slice : %v \n correct slice : %v", testSlice, correctSlice1)
	}

	if !reflect.DeepEqual(correctSlice1, correctSlice2) {
		t.Fatalf("shuffling doesnt work \n correct slice 1 : %v \n correct slice 2 : %v", correctSlice1, correctSlice2)
	}
}
