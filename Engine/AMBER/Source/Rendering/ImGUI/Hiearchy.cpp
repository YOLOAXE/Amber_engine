#include "Hiearchy.hpp"

namespace Ge
{
	Hiearchy::Hiearchy()
	{
		window_flags = 0;
		window_flags |= ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoResize;
		window_flags |= ImGuiWindowFlags_NoCollapse;
		window_flags |= ImGuiWindowFlags_NoInputs;
		window_flags |= ImGuiWindowFlags_NoFocusOnAppearing;
		window_flags |= ImGuiWindowFlags_NoNav;
	}

	void Hiearchy::render(VulkanMisc* vM)
	{
		std::vector<GObject *> items;
		std::vector<const char *> cnames;
		ImGui::SetNextWindowBgAlpha(0.55f);
		if (ImGui::Begin("Scene explorer", nullptr, window_flags))
		{
			ImGui::SetWindowPos("Scene explorer", ImVec2(0, 0));
			ImGui::SetWindowSize("Scene explorer", ImVec2(vM->str_VulkanSwapChainMisc->str_swapChainExtent.width / 4.2f, vM->str_VulkanSwapChainMisc->str_swapChainExtent.height / 1.4f));
			ImGui::TextColored(ImVec4(0.2f, 1, 0.2f, 1), "Hierarchy\n\n");

			ImGui::PushItemWidth(280);
			ImGui::ListBox("###Hierarchy", &m_listboxCurrentItem, cnames.data(), cnames.size(), 12);
			ImGui::PopItemWidth();

			ImGui::TextColored(ImVec4(0.2f, 1, 0.2f, 1), "Inspector\n\n");
			if (items.size() > 0)
			{
				ImGui::BeginChild("");
				items[m_listboxCurrentItem]->onGUI();
				ImGui::EndChild();
			}
		}
		ImGui::End();
	}
}