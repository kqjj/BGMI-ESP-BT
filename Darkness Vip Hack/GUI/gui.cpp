#include "gui.h"

using namespace ImGui;

bool ui::tab( int num ) {
    auto icon = tabs[num].m_icon;
    auto label = tabs[num].m_label;

    auto window = GetCurrentWindow( );
    auto style = GetStyle( );
    auto id = window->GetID( label );

    bool selected = num == next_tab;
    float selected_anim = ImTricks::Animations::FastFloatLerp( label, 0, selected, 0.f, 1.f, anim_speed );

    ImVec2 size( 46 + text_size( 1, icon ).x + int( ( CalcTextSize( label, 0, 1 ).x + 12 ) * selected_anim ), window->Size.y );
    ImVec2 p = window->DC.CursorPos;
    ImRect bb( p, p + size );

    ItemSize( bb );
    ItemAdd( bb, id );

    bool hovered, held;
    bool pressed = ButtonBehavior( bb, id, &hovered, &held );

    if ( pressed && !selected ) {
        content_anim_dest = 0.f;
        next_tab = num;
    }

    float anim = ImTricks::Animations::FastFloatLerp( label, 1, selected || hovered, 0.f, 1.f, anim_speed );

    auto icon_col = ImTricks::Animations::FastColorLerp( GetColorU32( ImGuiCol_TextDisabled ), GetColorU32(ImGuiCol_Text), anim );
    auto text_col = ImTricks::Animations::FastColorLerp( GetColorU32( ImGuiCol_TextDisabled, selected_anim ), GetColorU32( ImGuiCol_Text, selected_anim ), anim );

    window->DrawList->AddRectFilled( bb.Min, bb.Max, GetColorU32( ImGuiCol_FrameBg, selected_anim ) );
    window->DrawList->AddRectFilled( { bb.Min.x, bb.Max.y - 1 }, bb.Max, GetColorU32(ImGuiCol_Text, selected_anim ) );

    window->DrawList->AddText( font( 2 ), /*font(2)->FontSize*/ 25, {bb.Min.x + 23, bb.GetCenter().y - text_size(1, icon).y / 2}, icon_col, icon);
    window->DrawList->AddText( { bb.Max.x - CalcTextSize( label, 0, 1 ).x - 23,  bb.GetCenter( ).y - CalcTextSize( label, 0, 1 ).y / 2 }, text_col, label, FindRenderedTextEnd( label ) );

    return pressed;
}

int rotation_start_index;
void ui::rotate_start( )
{
    rotation_start_index = GetWindowDrawList( )->VtxBuffer.Size;
}

ImVec2 ui::text_size( int n, const char* text ) {
    return font( n )->CalcTextSizeA( font( n )->FontSize, FLT_MAX, -1, text, FindRenderedTextEnd( text ) );
}

ImVec2 ui::rotation_center( )
{
    ImVec2 l( FLT_MAX, FLT_MAX ), u( -FLT_MAX, -FLT_MAX );

    const auto& buf = GetWindowDrawList( )->VtxBuffer;
    for ( int i = rotation_start_index; i < buf.Size; i++ )
        l = ImMin( l, buf[i].pos ), u = ImMax( u, buf[i].pos );

    return ImVec2( ( l.x + u.x ) / 2, ( l.y + u.y ) / 2 );
}

void ui::rotate_end( float rad, ImVec2 center )
{
    float s = sin( rad ), c = cos( rad );
    center = ImRotate( center, s, c) - center;

    auto& buf = GetWindowDrawList()->VtxBuffer;
    for ( int i = rotation_start_index; i < buf.Size; i++ )
        buf[i].pos = ImRotate( buf[i].pos, s, c ) - center;
}

void ui::handle_alpha_anim( ) {
    content_anim = ImLerp( content_anim, content_anim_dest, anim_speed * 2.5f );

    if ( content_anim < 0.001f ) {
        content_anim_dest = 1.f;
        cur_page = next_tab;
    }
}

void ui::render_page( ) {
    if ( tabs[cur_page].pages.size( ) == 0 || tabs[cur_page].pages.size( ) <= tabs[cur_page].cur_subtab )
        return;

    tabs[cur_page].pages[tabs[cur_page].cur_subtab]( );
}

void ui::add_page( int tab, std::function< void( ) > code ) {
    tabs[tab].pages.emplace_back( code );
}

void ui::begin_child( const char* name, ImVec2 size ) {
    BeginChild( std::string( name ).append( "main" ).c_str( ), CalcItemSize( size, GetWindowWidth( ) / 2 - GImGui->Style.ItemSpacing.x / 2 - 20, 0 ) );

    GetWindowDrawList( )->AddText( GetWindowPos( ) + ImVec2{ 24, 30 - CalcTextSize( name ).y / 2 }, GetColorU32( ImGuiCol_Text ), name, FindRenderedTextEnd( name ) );
    GetWindowDrawList( )->AddRectFilled( GetWindowPos( ) + ImVec2{ 24, 59 }, GetWindowPos( ) + ImVec2{ GetWindowSize( ).x, 60 }, GetColorU32( ImGuiCol_Border ) );

    SetCursorPosY( 60 );
    PushStyleVar( ImGuiStyleVar_WindowPadding, { 24, 24 } );
    BeginChild( name, { -1, size.y == 0 ? size.y : -1 }, 0, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_AlwaysUseWindowPadding );
    PopStyleVar( );
    PushStyleVar( ImGuiStyleVar_ItemSpacing, { 18, 18 } );
}

void ui::end_child( ) {
    PopStyleVar( );
    EndChild( );
    EndChild( );
}

bool ui::color_btn( const char* str_id, float col[4], ImVec2 size ) {
    auto window = GetCurrentWindow( );
    auto style = GetStyle( );
    auto id = window->GetID( str_id );

    ImVec2 p = window->DC.CursorPos;
    ImRect bb( p, p + size );

    ItemSize( bb );
    ItemAdd( bb, id );

    bool hovered, held;
    bool pressed = ButtonBehavior( bb, id, &hovered, &held );

    window->DrawList->AddRectFilled( bb.Min, bb.Max, ImColor{ col[0], col[1], col[2], style.Alpha }, 2 );

    window->DrawList->AddRectFilled( { bb.GetCenter( ).x - bb.GetWidth( ) / 6, bb.Min.y }, { bb.GetCenter( ).x + bb.GetWidth( ) / 6, bb.GetCenter( ).y }, ImColor{ 1.f, 1.f, 1.f, GImGui->Style.Alpha * ( 1.f - col[3] ) * 0.6f } );
    window->DrawList->AddRectFilled( { bb.Min.x, bb.GetCenter( ).y }, { bb.Min.x + size.x / 3, bb.Max.y }, ImColor{ 1.f, 1.f, 1.f, GImGui->Style.Alpha * ( 1.f - col[3] ) * 0.6f }, 2, ImDrawFlags_RoundCornersBottomLeft );
    window->DrawList->AddRectFilled( { bb.Max.x - size.x / 3, bb.GetCenter( ).y }, bb.Max, ImColor{ 1.f, 1.f, 1.f, GImGui->Style.Alpha * ( 1.f - col[3] ) * 0.6f }, 2, ImDrawFlags_RoundCornersBottomRight );

    return pressed;
}

void ui::multi_select( const char* label, std::vector< multi_select_item >& items ) {
    auto window = GetCurrentWindow( );
    auto id = window->GetID( label );

    std::string buf;

    buf.clear( );
    for ( size_t i = 0; i < items.size( ); ++i ) {
        if ( items[i] ) {
            buf += items[i].label;
            buf += ", ";
        }
    }

    if ( !buf.empty( ) ) {
        buf.resize( buf.size( ) - 2 );
    }

    const ImGuiID popup_id = ImHashStr( "##ComboPopup", 0, id );
    bool popup_open = IsPopupOpen( popup_id, ImGuiPopupFlags_None );

    if ( popup_open )
        SetNextWindowSizeConstraints( ImVec2( 0, 0 ), ImVec2( FLT_MAX, 30 * items.size( ) + 20 ) );

    if ( !BeginCombo( label, buf.c_str( ) ) )
        return;

    SetCursorPos( { 0, 10 } );
    BeginGroup( );

    PushStyleVar( ImGuiStyleVar_ItemSpacing, { 0, 0 } );
    for ( int i = 0; i < items.size( ); ++i ) {
        if ( Selectable( items[i].label, items[i], ImGuiSelectableFlags_NoPadWithHalfSpacing | ImGuiSelectableFlags_DontClosePopups, { 0, 30 } ) )
            items[i].selected = !items[i].selected;
    }
    PopStyleVar( );

    EndGroup( );
    EndCombo( );
}

void ui::styles() {

    auto& style = ImGui::GetStyle();
    style.TabRounding = 4;
    style.ScrollbarRounding = 9;
    style.WindowRounding = 7;
    style.GrabRounding = 3;
    style.FrameRounding = 3;
    style.PopupRounding = 4;
    style.ChildRounding = 4;

    style.GrabMinSize = 40.0f;

    style.ScrollbarRounding = 0;  // Set to 0 to remove any visible scrollbar rounding
    style.ScrollbarSize = 0.0f;  // Make scrollbar size zero to hide it completely
  //  style.ScrollbarSize = 12.0f;  // Example: Set a non-zero scrollbar size

}

void ui::colors() {
    auto& colors = ImGui::GetStyle().Colors;

    // Dark background for windows and menu bar
    colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.1f, 0.13f, 1.0f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.16f, 0.16f, 0.21f, 1.0f);

    // Background for child windows
    colors[ImGuiCol_ChildBg] = ImVec4(0.13f, 0.13f, 0.17f, 1.0f);

    // Border and shadow colors
    colors[ImGuiCol_Border] = ImVec4(0.44f, 0.37f, 0.61f, 0.29f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.24f);

    // Text colors
    colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);

    // Header colors
    colors[ImGuiCol_Header] = ImVec4(0.13f, 0.13f, 0.17f, 1.0f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.19f, 0.2f, 0.25f, 1.0f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.16f, 0.16f, 0.21f, 1.0f);

    // Button colors
    colors[ImGuiCol_Button] = ImVec4(0.44f, 0.37f, 0.61f, 1.0f); // Adjusted to opaque
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.19f, 0.2f, 0.25f, 1.0f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.16f, 0.16f, 0.21f, 1.0f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.74f, 0.58f, 0.98f, 1.0f);

    // Popup background color
    colors[ImGuiCol_PopupBg] = ImVec4(0.1f, 0.1f, 0.13f, 0.92f);

    // Slider colors
    colors[ImGuiCol_SliderGrab] = ImVec4(0.44f, 0.37f, 0.61f, 1.0f); // Adjusted to opaque
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.74f, 0.58f, 0.98f, 0.54f);

    // Frame background colors with opaque backgrounds
    colors[ImGuiCol_FrameBg] = ImVec4(0.1f, 0.1f, 0.13f, 1.0f);         // Normal state
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.15f, 0.15f, 0.18f, 1.0f);  // Hovered state
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.12f, 0.12f, 0.15f, 1.0f);    // Active (clicked) state


    // Tab colors
    colors[ImGuiCol_Tab] = ImVec4(0.16f, 0.16f, 0.21f, 1.0f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.24f, 0.24f, 0.32f, 1.0f);
    colors[ImGuiCol_TabActive] = ImVec4(0.2f, 0.22f, 0.27f, 1.0f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.16f, 0.16f, 0.21f, 1.0f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.16f, 0.16f, 0.21f, 1.0f);

    // Title bar colors
    colors[ImGuiCol_TitleBg] = ImVec4(0.16f, 0.16f, 0.21f, 1.0f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.16f, 0.16f, 0.21f, 1.0f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.16f, 0.16f, 0.21f, 1.0f);

    // Scrollbar colors
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.1f, 0.1f, 0.13f, 1.0f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.16f, 0.16f, 0.21f, 1.0f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.19f, 0.2f, 0.25f, 1.0f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.24f, 0.24f, 0.32f, 1.0f);

    // Separator colors
    colors[ImGuiCol_Separator] = ImVec4(0.44f, 0.37f, 0.61f, 1.0f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.74f, 0.58f, 0.98f, 1.0f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.84f, 0.58f, 1.0f, 1.0f);

    // Resize grip colors
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.44f, 0.37f, 0.61f, 0.29f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.74f, 0.58f, 0.98f, 0.29f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.84f, 0.58f, 1.0f, 0.29f);


}
