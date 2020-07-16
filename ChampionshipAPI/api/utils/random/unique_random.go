package random

import (
	"math/rand"
	"time"
)

// ShuffleUint64 shuffle uint64 slice
func ShuffleUint64(values *[]uint64) {
	rand.Seed(time.Now().UnixNano())
	rand.Shuffle(len(*values), func(i, j int) { (*values)[i], (*values)[j] = (*values)[j], (*values)[i] })

}
