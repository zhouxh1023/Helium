#include "ReflectArrayInterpreter.h"
#include "InspectReflectInit.h"

#include "Application/Inspect/Controls/InspectLabel.h"
#include "Application/Inspect/Controls/InspectValue.h"
#include "Application/Inspect/Controls/InspectChoice.h"
#include "Application/Inspect/Controls/InspectList.h"
#include "Application/Inspect/Controls/InspectButton.h"
#include "Application/Inspect/InspectData.h"
#include "Application/Inspect/InspectInit.h"

#include "Foundation/String/Tokenize.h"

using namespace Helium;
using namespace Helium::Reflect;
using namespace Helium::Inspect;

ReflectArrayInterpreter::ReflectArrayInterpreter (Container* labelContainer)
: ReflectFieldInterpreter (labelContainer)
{

}

void ReflectArrayInterpreter::InterpretField(const Field* field, const std::vector<Reflect::Element*>& instances, Container* parent)
{
  if (field->m_Flags & FieldFlags::Hide)
  {
    return;
  }

  // create the label
  ContainerPtr labelContainer = m_Container->GetCanvas()->Create<Container>(this);
  parent->AddChild( labelContainer );
  LabelPtr label = labelContainer->GetCanvas()->Create<Label>(this);
  labelContainer->AddChild( label );
  tstring temp;
  bool converted = Helium::ConvertString( field->m_UIName, temp );
  HELIUM_ASSERT( converted );
  label->SetText( temp );

  // create the list view
  ContainerPtr listContainer = m_Container->GetCanvas()->Create<Container>(this);
  parent->AddChild( listContainer );
  ListPtr list = m_Container->GetCanvas()->Create<List>(this);
  listContainer->AddChild( list );

  // create the buttons
  ButtonPtr addButton;
  ButtonPtr removeButton;
  ButtonPtr upButton;
  ButtonPtr downButton;
  if ( !(field->m_Flags & FieldFlags::ReadOnly) )
  {
    addButton = AddAddButton( list );
    removeButton = AddRemoveButton( list );
    upButton = AddMoveUpButton( list );
    downButton = AddMoveDownButton( list );
  }

  // add the buttons to the panel
  ContainerPtr buttonGroup = m_Container->GetCanvas()->Create<Container>(this);
  parent->AddChild( buttonGroup );
  if ( addButton )
  {
    buttonGroup->AddChild( addButton );
  }
  if ( removeButton )
  {
    buttonGroup->AddChild( removeButton );
  }
  if ( upButton )
  {
    buttonGroup->AddChild( upButton );
  }
  if ( downButton )
  {
    buttonGroup->AddChild( downButton );
  }

  // create the serializers
  std::vector<Reflect::Element*>::const_iterator itr = instances.begin();
  std::vector<Reflect::Element*>::const_iterator end = instances.end();
  for ( ; itr != end; ++itr )
  {
    SerializerPtr s = field->CreateSerializer();

    OnCreateFieldSerializer( s );

    s->ConnectField(*itr, field);

    m_Serializers.push_back(s);
  }

  // bind the ui to the serializers
  Helium::SmartPtr< MultiStringFormatter<Serializer> > data = new MultiStringFormatter<Reflect::Serializer>( (std::vector<Reflect::Serializer*>&)m_Serializers );
  list->Bind( data );

  // setup the default value
  if (field->m_Default != NULL)
  {
    tstringstream outStream;
    *field->m_Default >> outStream;
    list->SetDefault( outStream.str() );
  }
}

ButtonPtr ReflectArrayInterpreter::AddAddButton( List* list )
{
  ButtonPtr addButton = m_Container->GetCanvas()->Create<Button>(this);
  addButton->ButtonClickedEvent().Add( ButtonSignature::Delegate ( &ReflectArrayInterpreter::OnAdd ) );
  addButton->SetClientData( new ClientData( list ) );
  addButton->SetText( TXT( "Add" ) );

  return addButton;
}

ButtonPtr ReflectArrayInterpreter::AddRemoveButton( List* list )
{
  ButtonPtr removeButton = m_Container->GetCanvas()->Create<Button>(this);
  removeButton->SetText( TXT( "Remove" ) );
  removeButton->ButtonClickedEvent().Add( ButtonSignature::Delegate ( &ReflectArrayInterpreter::OnRemove ) );
  removeButton->SetClientData( new ClientData( list ) );
  
  return removeButton;
}

ButtonPtr ReflectArrayInterpreter::AddMoveUpButton( List* list )
{
  ButtonPtr upButton = m_Container->GetCanvas()->Create<Button>(this);
  upButton->SetIcon( TXT( "actions/go-up" ) );
  upButton->ButtonClickedEvent().Add( ButtonSignature::Delegate ( &ReflectArrayInterpreter::OnMoveUp ) );
  upButton->SetClientData( new ClientData( list ) );
  
  return upButton;
}

ButtonPtr ReflectArrayInterpreter::AddMoveDownButton( List* list )
{
  ButtonPtr downButton = m_Container->GetCanvas()->Create<Button>(this);
  downButton->SetIcon( TXT( "actions/go-down" ) );
  downButton->ButtonClickedEvent().Add( ButtonSignature::Delegate ( &ReflectArrayInterpreter::OnMoveDown ) );
  downButton->SetClientData( new ClientData( list ) );
  
  return downButton;
}

void ReflectArrayInterpreter::OnAdd( Button* button )
{
  Reflect::ObjectPtr clientData = button->GetClientData();
  if ( clientData.ReferencesObject() && clientData->HasType( Reflect::GetType<ClientData>() ) )
  {
    ClientData* data = static_cast< ClientData* >( clientData.Ptr() );
    wxTextEntryDialog dlg( button->GetCanvas()->GetControl(), TXT( "" ), TXT( "Add" ) );
    if ( dlg.ShowModal() == wxID_OK )
    {
      tstring input = dlg.GetValue().c_str();
      if ( !input.empty() )
      {
        List* list = static_cast< List* >( data->m_Control );
        list->AddItem( input );
      }
    }

    button->GetCanvas()->Read();
  }
}

void ReflectArrayInterpreter::OnRemove( Button* button )
{
  Reflect::ObjectPtr clientData = button->GetClientData();
  if ( clientData.ReferencesObject() && clientData->HasType( Reflect::GetType<ClientData>() ) )
  {
    ClientData* data = static_cast< ClientData* >( clientData.Ptr() );
    List* list = static_cast< List* >( data->m_Control );
    const std::vector< tstring >& selectedItems = list->GetSelectedItems();
    if ( !selectedItems.empty() )
    {
      std::vector< tstring >::const_iterator itr = selectedItems.begin();
      std::vector< tstring >::const_iterator end = selectedItems.end();
      list->Freeze();
      for ( ; itr != end; ++itr )
      {
        const tstring& selection = *itr;
        list->RemoveItem( selection );
      }
      list->Thaw();
    }
  }
}

void ReflectArrayInterpreter::OnMoveUp( Button* button )
{
  Reflect::ObjectPtr clientData = button->GetClientData();
  if ( clientData.ReferencesObject() && clientData->HasType( Reflect::GetType<ClientData>() ) )
  {
    ClientData* data = static_cast< ClientData* >( clientData.Ptr() );
    List* list = static_cast< List* >( data->m_Control );
    list->MoveSelectedItems( Inspect::MoveDirections::Up );
  }
}

void ReflectArrayInterpreter::OnMoveDown( Button* button )
{
  Reflect::ObjectPtr clientData = button->GetClientData();
  if ( clientData.ReferencesObject() && clientData->HasType( Reflect::GetType<ClientData>() ) )
  {
    ClientData* data = static_cast< ClientData* >( clientData.Ptr() );
    List* list = static_cast< List* >( data->m_Control );
    list->MoveSelectedItems( Inspect::MoveDirections::Down );
  }
}