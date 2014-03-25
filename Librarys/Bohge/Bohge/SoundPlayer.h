#pragma once
#include "3DMath.h"
#include "SoundManager.h"



namespace BohgeEngine
{
	class SoundResource;
	class SoundPlayer
	{
		friend class SoundManager;
	private:
		enum SoundSourceFlag
		{
			SSF_PAUSED			=	1UL << 0,
			SSF_LOOP			=	1UL << 1,
			SSF_PLAYING			=	1UL << 2,
			SSF_IS3D			=	1UL << 3,
		};
	private:
		int				m_nIndex;
		uint			m_nHashCode;
		float			m_fVolume;
		float			m_fPitch;
		int				m_nFlag;
		SoundResource*	m_pResource;
	protected:
		SoundPlayer( uint hash, int index, Decoder* res );
		virtual ~SoundPlayer(void);
	private:
		virtual void _DoSetVolume( float volume ) = 0;
		virtual void _DoSetPitch(float pitch) = 0;
		virtual void _DoSetPaused( bool ispaused ) = 0;
		virtual void _DoSetLoop( bool isloop ) = 0;
		virtual void _DoSetPlay( bool isplay ) = 0;
		virtual void _DoSet3D( bool is3d ) = 0;
		virtual void _DoSetSoundPosition( const vector3f& pos, const vector3f& forward, const vector3f& up ) = 0;
		virtual void _DoUpdate() = 0;
	public:
		void Update();
	public:
		void Initialization();
	private:
		BOHGE_FORCEINLINE void _SetFlag( bool isflag, SoundSourceFlag flag )
		{
			isflag ? m_nFlag |= flag : m_nFlag &= ~flag;
		}
		BOHGE_FORCEINLINE bool _GetFlag( SoundSourceFlag flag ) const
		{
			return 0 != ( m_nFlag & flag );
		}
	protected:
		BOHGE_FORCEINLINE SoundResource* _GetSoundResource()
		{
			return m_pResource;
		}
		BOHGE_FORCEINLINE void _OnPlayDone()//��ɲ���
		{
			if ( !_GetFlag(SSF_LOOP) )
			{
				Stop();
			}
		}
	public:
		BOHGE_FORCEINLINE int GetIndex() const
		{
			return m_nIndex;
		}
		BOHGE_FORCEINLINE uint GetHashCode() const
		{
			return m_nHashCode;
		}
		BOHGE_FORCEINLINE void Release( )
		{
			SoundManager::Instance()->ReleaseSound( this );
		}
		BOHGE_FORCEINLINE void SetVolume( float volume )
		{
			m_fVolume = volume;
			_DoSetVolume( volume * SoundManager::Instance()->GetGlobalVolume() );
		}
		BOHGE_FORCEINLINE float GetVolume() const
		{
			return m_fVolume;
		}
		BOHGE_FORCEINLINE void SetPitch( float pitch )
		{
			m_fPitch = pitch;
			_DoSetPitch( pitch * SoundManager::Instance()->GetGlobalPitch() );
		}
		BOHGE_FORCEINLINE float GetPitch() const
		{
			return m_fPitch;
		}
		BOHGE_FORCEINLINE void SetPaused( bool ispaused )
		{
			_SetFlag( ispaused, SSF_PAUSED );
			_DoSetPaused( ispaused );
		}
		BOHGE_FORCEINLINE bool isPaused( ) const
		{
			return _GetFlag( SSF_PAUSED );
		}
		BOHGE_FORCEINLINE void SetLoop( bool isloop )
		{
			_SetFlag( isloop, SSF_LOOP );
			_DoSetLoop( isloop );
		}
		BOHGE_FORCEINLINE bool isLoop( ) const
		{
			return _GetFlag( SSF_LOOP );
		}
		BOHGE_FORCEINLINE void Paly( )
		{
			_SetFlag( true, SSF_PLAYING );
			SetPaused( false );
			_DoSetPlay( true );
		}
		BOHGE_FORCEINLINE void Stop()
		{
			_SetFlag( false, SSF_PLAYING );
			_DoSetPlay( false );
		}
		BOHGE_FORCEINLINE bool isPlaying( ) const
		{
			return _GetFlag( SSF_PLAYING ) & !_GetFlag( SSF_PAUSED );
		}
		BOHGE_FORCEINLINE bool Set3D( bool is3D )
		{
			_SetFlag( is3D, SSF_IS3D );
			_DoSet3D( is3D );
		}
		BOHGE_FORCEINLINE bool is3D( ) const
		{
			_GetFlag( SSF_IS3D );
		}
	};

}