#pragma once

class SlimRWLock
{
public:
	SlimRWLock()
	{
		::InitializeSRWLock(&srwLock_);
	}

	void LockReader() 
	{
		::AcquireSRWLockShared(&srwLock_);
	}

	void LockWriter()
	{
		::AcquireSRWLockExclusive(&srwLock_);
	}

	void UnlockReader()
	{
		::ReleaseSRWLockShared(&srwLock_);
	}

	void UnlockWriter()
	{
		::ReleaseSRWLockExclusive(&srwLock_);
	}

	DWORD numberReaderRacesLost() const
	{
		return 0;
	}

	DWORD numberReaderWakeups() const
	{
		return 0;
	}

	LONGLONG locked_acquiringLockExclusive(void) const
	{
		return 0L;
	}
	LONGLONG locked_acquiringLockShared(void) const
	{
		return 0L;
	}

private:
	SRWLOCK srwLock_;
};

