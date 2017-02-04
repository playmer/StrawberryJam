#pragma once

#include <stddef.h>

template <typename HandleType, typename DestructionFunction = void(*)(HandleType)>
class UniqueHandle
{
  public:

  UniqueHandle()
    : mHandle(HandleType()), mDestructor(nullptr)
  {

  }

  UniqueHandle(HandleType &aHandle, DestructionFunction aDestructor)
    : mHandle(aHandle), mDestructor(aDestructor)
  {

  }

  UniqueHandle& operator=(const UniqueHandle &) = delete;
  UniqueHandle(const UniqueHandle &) = delete;

  UniqueHandle(UniqueHandle &&rhs)
  {
    mDestructor = rhs.mDestructor;
    mDestructor = rhs.mDestructor;

    rhs.mDestructor = nullptr;
    rhs.mHandle = HandleType();
  }

  HandleType get()
  {
    return mHandle;
  }

  void release()
  {
    if (nullptr != mDestructor)
    {
      mDestructor(mHandle);
      mDestructor = nullptr;
      mHandle = HandleType();
    }
  }

  ~UniqueHandle()
  {
    release();
  }

  private:
  HandleType mHandle;
  DestructionFunction mDestructor;
};
