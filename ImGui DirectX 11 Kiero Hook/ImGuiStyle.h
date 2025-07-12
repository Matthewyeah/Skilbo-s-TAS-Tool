#pragma once
#include "imgui/imgui.h"

void SetupImGuiStyle()
{
	// Skilbo'sTASTool style from ImThemes
	ImGuiStyle& style = ImGui::GetStyle();

	style.Alpha = 1.0f;
	style.WindowPadding = ImVec2(10.0f, 6.0f);
	style.WindowRounding = 5.0f;
	style.WindowBorderSize = 1.0f;
	style.WindowMinSize = ImVec2(32.0f, 32.0f);
	style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
	style.WindowMenuButtonPosition = ImGuiDir_Left;
	style.ChildRounding = 0.0f;
	style.ChildBorderSize = 1.0f;
	style.PopupRounding = 0.0f;
	style.PopupBorderSize = 1.0f;
	style.FramePadding = ImVec2(4.0f, 4.0f);
	style.FrameRounding = 5.0f;
	style.FrameBorderSize = 0.0f;
	style.ItemSpacing = ImVec2(8.0f, 4.0f);
	style.ItemInnerSpacing = ImVec2(4.0f, 4.0f);
	style.IndentSpacing = 21.0f;
	style.ColumnsMinSpacing = 6.0f;
	style.ScrollbarSize = 14.0f;
	style.ScrollbarRounding = 9.0f;
	style.GrabMinSize = 10.0f;
	style.GrabRounding = 5.0f;
	style.TabRounding = 5.0f;
	style.TabBorderSize = 0.0f;
	style.ColorButtonPosition = ImGuiDir_Right;
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
	style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

	style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.4980392158031464f, 0.4980392158031464f, 0.4980392158031464f, 1.0f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(9.999999974752427e-07f, 9.999899930335232e-07f, 9.999899930335232e-07f, 0.9f);
	style.Colors[ImGuiCol_ChildBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.4901960790157318f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.2274509817361832f, 0.2588235437870026f, 0.2980392277240753f, 1.0f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(9.999999974752427e-07f, 9.999899930335232e-07f, 9.999899930335232e-07f, 0.0f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.06666667014360428f, 0.1568627506494522f, 0.1725490242242813f, 1.0f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.2627451121807098f, 0.3568627536296844f, 0.3607843220233917f, 1.0f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.2627451121807098f, 0.3568627536296844f, 0.3607843220233917f, 1.0f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.03921568766236305f, 0.03921568766236305f, 0.03921568766236305f, 1.0f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.03921568766236305f, 0.03921568766236305f, 0.03921568766236305f, 1.0f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.0f, 0.0f, 0.0f, 0.5099999904632568f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.1372549086809158f, 0.1372549086809158f, 0.1372549086809158f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.01960784383118153f, 0.01960784383118153f, 0.01960784383118153f, 0.5299999713897705f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.3098039329051971f, 0.3098039329051971f, 0.3098039329051971f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.407843142747879f, 0.407843142747879f, 0.407843142747879f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.5098039507865906f, 0.5098039507865906f, 0.5098039507865906f, 1.0f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.9999899864196777f, 0.9999945759773254f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.5915010571479797f, 0.6168811917304993f, 0.6180257797241211f, 1.0f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.5921568870544434f, 0.615686297416687f, 0.6196078658103943f, 1.0f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.2627451121807098f, 0.3568627536296844f, 0.3607843220233917f, 1.0f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.0f, 0.5607843399047852f, 0.5686274766921997f, 1.0f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.005968042183667421f, 0.6857762336730957f, 0.6952790021896362f, 1.0f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.06666667014360428f, 0.1568627506494522f, 0.1725490242242813f, 1.0f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.1264344453811646f, 0.2600286602973938f, 0.283261775970459f, 1.0f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.2627451121807098f, 0.3568627536296844f, 0.3607843220233917f, 1.0f);
	style.Colors[ImGuiCol_Separator] = ImVec4(0.4274509847164154f, 0.4274509847164154f, 0.4980392158031464f, 0.5f);
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.2627451121807098f, 0.3568627536296844f, 0.3607843220233917f, 1.0f);
	style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.2627451121807098f, 0.3568627536296844f, 0.3607843220233917f, 1.0f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.06666667014360428f, 0.1568627506494522f, 0.1725490242242813f, 1.0f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.2627451121807098f, 0.3568627536296844f, 0.3607843220233917f, 1.0f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.0f, 0.5607843399047852f, 0.5686274766921997f, 1.0f);
	style.Colors[ImGuiCol_Tab] = ImVec4(0.06666667014360428f, 0.1568627506494522f, 0.1725490242242813f, 1.0f);
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.2627451121807098f, 0.3568627536296844f, 0.3607843220233917f, 1.0f);
	style.Colors[ImGuiCol_TabActive] = ImVec4(0.2627451121807098f, 0.3568627536296844f, 0.3607843220233917f, 1.0f);
	style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.06666667014360428f, 0.1019607856869698f, 0.1450980454683304f, 0.9724000096321106f);
	style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.06666667014360428f, 0.1019607856869698f, 0.1450980454683304f, 0.9725490212440491f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.6078431606292725f, 0.6078431606292725f, 0.6078431606292725f, 1.0f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.0f, 0.4274509847164154f, 0.3490196168422699f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.8980392217636108f, 0.6980392336845398f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.0f, 0.6000000238418579f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 0.3499999940395355f);
	style.Colors[ImGuiCol_DragDropTarget] = ImVec4(1.0f, 1.0f, 0.0f, 0.8999999761581421f);
	style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 1.0f);
	style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.0f, 1.0f, 1.0f, 0.699999988079071f);
	style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.2000000029802322f);
	style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.3499999940395355f);
}
