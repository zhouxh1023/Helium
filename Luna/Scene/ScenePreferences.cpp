#include "Precompile.h"
#include "ScenePreferences.h"

#include "Application/Preferences.h"

using namespace Luna;

///////////////////////////////////////////////////////////////////////////////
// Globals, statics, etc.
///////////////////////////////////////////////////////////////////////////////

// Increment this value to invalidate just the window settings for the Scene Editor
const static tstring s_WindowSettingsVersion( TXT( "11" ) );

ScenePreferences::ScenePreferences()
: m_MRU( new MRUData() )
, m_WindowSettings( new WindowSettings( s_WindowSettingsVersion ) )
, m_DefaultNodeVisibility( new Content::NodeVisibility() )
, m_ScaleManipulatorSize( 0.3f )
, m_RotateManipulatorSize( 0.3f )
, m_RotateManipulatorAxisSnap( false )
, m_RotateManipulatorSnapDegrees( 15.0f )
, m_RotateManipulatorSpace( ManipulatorSpaces::Object )
, m_TranslateManipulatorSize( 0.3f )
, m_TranslateManipulatorSpace( ManipulatorSpaces::Object )
, m_TranslateManipulatorSnappingMode( TranslateSnappingModes::None )
, m_TranslateManipulatorDistance( 1.0f )
, m_TranslateManipulatorLiveObjectsOnly( false )
, m_ScaleManipulatorGridSnap( false )
, m_ScaleManipulatorDistance( 1.0f )
{
}

MRUData* ScenePreferences::GetMRU()
{
    return m_MRU;
}

WindowSettings* ScenePreferences::GetWindowSettings()
{
    return m_WindowSettings;
}

Content::NodeVisibility* ScenePreferences::GetDefaultNodeVisibility()
{
    return m_DefaultNodeVisibility; 
}

const Reflect::Field* ScenePreferences::ScaleManipulatorSize() const
{
    return GetClass()->FindField( &ScenePreferences::m_ScaleManipulatorSize );
}

const Reflect::Field* ScenePreferences::RotateManipulatorSize() const
{
    return GetClass()->FindField( &ScenePreferences::m_RotateManipulatorSize );
}

const Reflect::Field* ScenePreferences::RotateManipulatorAxisSnap() const
{
    return GetClass()->FindField( &ScenePreferences::m_RotateManipulatorAxisSnap );
}

const Reflect::Field* ScenePreferences::RotateManipulatorSnapDegrees() const
{
    return GetClass()->FindField( &ScenePreferences::m_RotateManipulatorSnapDegrees );
}

const Reflect::Field* ScenePreferences::RotateManipulatorSpace() const
{
    return GetClass()->FindField( &ScenePreferences::m_RotateManipulatorSpace );
}

const Reflect::Field* ScenePreferences::TranslateManipulatorSize() const
{
    return GetClass()->FindField( &ScenePreferences::m_TranslateManipulatorSize );
}

const Reflect::Field* ScenePreferences::TranslateManipulatorSpace() const
{
    return GetClass()->FindField( &ScenePreferences::m_TranslateManipulatorSpace );
}

const Reflect::Field* ScenePreferences::TranslateManipulatorSnappingMode() const
{
    return GetClass()->FindField( &ScenePreferences::m_TranslateManipulatorSnappingMode );
}

const Reflect::Field* ScenePreferences::TranslateManipulatorDistance() const
{
    return GetClass()->FindField( &ScenePreferences::m_TranslateManipulatorDistance );
}

const Reflect::Field* ScenePreferences::TranslateManipulatorLiveObjectsOnly() const
{
    return GetClass()->FindField( &ScenePreferences::m_TranslateManipulatorLiveObjectsOnly );
}

const Reflect::Field* ScenePreferences::ScaleManipulatorGridSnap() const
{
    return GetClass()->FindField( &ScenePreferences::m_ScaleManipulatorGridSnap );
}

const Reflect::Field* ScenePreferences::ScaleManipulatorDistance() const
{
    return GetClass()->FindField( &ScenePreferences::m_ScaleManipulatorDistance );
}
