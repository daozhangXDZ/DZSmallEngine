#pragma once
#include "Platform.h"
class FThreadSafeCounter
{
public:
	typedef int32 IntegerType;

	/**
	 * Default constructor.
	 *
	 * Initializes the counter to 0.
	 */
	FThreadSafeCounter()
	{
		Counter = 0;
	}

	/**
	 * Copy Constructor.
	 *
	 * If the counter in the Other parameter is changing from other threads, there are no
	 * guarantees as to which values you will get up to the caller to not care, synchronize
	 * or other way to make those guarantees.
	 *
	 * @param Other The other thread safe counter to copy
	 */
	FThreadSafeCounter(const FThreadSafeCounter& Other)
	{
		Counter = Other.GetValue();
	}

	/**
	 * Constructor, initializing counter to passed in value.
	 *
	 * @param Value	Value to initialize counter to
	 */
	FThreadSafeCounter(int32 Value)
	{
		Counter = Value;
	}

	/**
	 * Increment and return new value.
	 *
	 * @return the new, incremented value
	 * @see Add, Decrement, Reset, Set, Subtract
	 */
	int32 Increment()
	{
		Counter++;
		return Counter;
	}

	/**
	 * Adds an amount and returns the old value.
	 *
	 * @param Amount Amount to increase the counter by
	 * @return the old value
	 * @see Decrement, Increment, Reset, Set, Subtract
	 */
	int32 Add(int32 Amount)
	{
		Counter += Amount;
		return Counter;
	}

	/**
	 * Decrement and return new value.
	 *
	 * @return the new, decremented value
	 * @see Add, Increment, Reset, Set, Subtract
	 */
	int32 Decrement()
	{
		Counter--;
		return Counter;
	}

	/**
	 * Subtracts an amount and returns the old value.
	 *
	 * @param Amount Amount to decrease the counter by
	 * @return the old value
	 * @see Add, Decrement, Increment, Reset, Set
	 */
	int32 Subtract(int32 Amount)
	{
		Counter -= Amount;
		return Counter;
	}

	/**
	 * Sets the counter to a specific value and returns the old value.
	 *
	 * @param Value	Value to set the counter to
	 * @return The old value
	 * @see Add, Decrement, Increment, Reset, Subtract
	 */
	int32 Set(int32 Value)
	{
		Counter = Value;
		return Counter;
	}

	/**
	 * Resets the counter's value to zero.
	 *
	 * @return the old value.
	 * @see Add, Decrement, Increment, Set, Subtract
	 */
	int32 Reset()
	{
		Counter = 0;
		return Counter;
	}

	/**
	 * Gets the current value.
	 *
	 * @return the current value
	 */
	int32 GetValue() const
	{
		return Counter;
	}

private:

	/** Hidden on purpose as usage wouldn't be thread safe. */
	void operator=(const FThreadSafeCounter& Other) {}

	/** Thread-safe counter */
	volatile int32 Counter;
};