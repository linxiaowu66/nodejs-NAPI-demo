#include <napi.h>
#include "./sort.cc"

#define QUICK_SORT 0
#define BUBBLE_SORT 1

using namespace Napi;

napi_value Sort(const CallbackInfo &info)
{
  // get an environment in which method is being run
  Env env = info.Env();
  if (info.Length() < 2)
  {
    TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
    return env.Null();
  }
  if (!info[0].IsArray())
  {
    TypeError::New(env, "Wrong first argument").ThrowAsJavaScriptException();
    return env.Null();
  }
  if (!info[1].IsNumber())
  {
    TypeError::New(env, "Wrong second argument").ThrowAsJavaScriptException();
    return env.Null();
  }
  // get the method input params: array to sort and sorting type ('quick' or 'bubble')
  const Array inputArray = info[0].As<Array>();
  const int sortType = info[1].As<Number>().Uint32Value();

  // get the input array length, create an empty array of unsigned integers with the length of the input array
  unsigned int length = inputArray.Length();
  unsigned int array[length];
  unsigned int i;

  // get values from the input array as unsigned integers and copy them to the blank array
  for (i = 0; i < length; i++)
  {
    array[i] = inputArray[i].As<Number>().Uint32Value();
  }
  unsigned int *arrayPointer = &array[0];

  // passing the array pointer to the sorting method
  switch (sortType)
  {
  case BUBBLE_SORT:
    bubbleSort(arrayPointer, length);
    break;
  case QUICK_SORT:
    quickSort(arrayPointer, length);
    break;
  default:
    break;
  }

  // create an output array
  Array outputArray = Array::New(env, length);
  for (i = 0; i < length; i++)
  {
    outputArray[i] = Number::New(env, uint32_t(array[i]));
  }
  return outputArray;
}

Object Init(Env env, Object exports)
{
  exports.Set(String::New(env, "sort"), Function::New(env, Sort));
  return exports;
}

NODE_API_MODULE(addon, Init)
