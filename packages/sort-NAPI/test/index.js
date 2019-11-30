const addon = require('../build/Release/sort-napi')

const QUICK_SORT = 0
const BUBBLE_SORT = 1
const ARRAY_LENGTH = 1000000

const targetArray = Array(ARRAY_LENGTH)
  .fill(null)
  .map(() => Math.round(Math.random() * 1000))


  const sortedArrayJSBubble = [...targetArray]

  const defaultComparator = (a, b) => {
    if (a < b) {
      return -1
    }
    if (a > b) {
      return 1
    }
    return 0
  }

  const quickSort = ( unsortedArray, comparator = defaultComparator) => {
    const sortedArray = [ ...unsortedArray ]
    const recursiveSort = (start, end) => {
      if (end - start < 1) {
        return
      }
      const pivotValue = sortedArray[end]
      let splitIndex = start
      for (let i = start; i < end; i++) {
        const sort = comparator(sortedArray[i], pivotValue)
        if (sort === -1) {
          if (splitIndex !== i) {
            const temp = sortedArray[splitIndex]
            sortedArray[splitIndex] = sortedArray[i]
            sortedArray[i] = temp
          }
          splitIndex++
        }
      }
      sortedArray[end] = sortedArray[splitIndex]
      sortedArray[splitIndex] = pivotValue
      recursiveSort(start, splitIndex - 1)
      recursiveSort(splitIndex + 1, end)
    }
    recursiveSort(0, unsortedArray.length - 1)
    return sortedArray
  }

  console.time('JS quick sort')

  const sortedArrayJS = quickSort(targetArray)

  console.timeEnd('JS quick sort')
  console.log(`sortedArrayJS length: ${sortedArrayJS.length}`)

  console.time('JS bubble sort')
  for (let i = 0; i < sortedArrayJSBubble.length - 1; ++i) {
    for (let j = 0; j < sortedArrayJSBubble.length - 1 - i; ++j) {
      if (sortedArrayJSBubble[j] > sortedArrayJSBubble[j + 1]) {
        const temp = sortedArrayJSBubble[j + 1]
        sortedArrayJSBubble[j + 1] = sortedArrayJSBubble[j]
        sortedArrayJSBubble[j] = temp
      }
    }
  }
  console.timeEnd('JS bubble sort')
  console.log(`sortedArrayJSBubble length: ${sortedArrayJSBubble.length}`)

  console.time('N-API bubble sort')
  const sortedArrayCbubble = addon.sort(targetArray, BUBBLE_SORT)
  console.timeEnd('N-API bubble sort')
  console.log(`sortedArrayCbubble length: ${sortedArrayCbubble.length}`)

  console.time('N-API quick sort')
  const sortedArrayCquick = addon.sort(targetArray, QUICK_SORT)
  console.timeEnd('N-API quick sort')
  console.log(`sortedArrayCquick length: ${sortedArrayCquick.length}`)
