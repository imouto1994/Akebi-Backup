#include "pch-il2cpp.h"
#include "AssetDump.h"

#include <helpers.h>

namespace cheat::feature
{
	static uint64_t CommonMiscs_GetAssetPathHash_1_Hook(app::String* path, app::String* extention, MethodInfo* method);

	AssetDump::AssetDump() : Feature(),
		NF(f_Enabled, "Asset Dump", "AssetDump", false)
	{
		HookManager::install(app::CommonMiscs_GetAssetPathHash_1, CommonMiscs_GetAssetPathHash_1_Hook);
	}

	const FeatureGUIInfo& AssetDump::GetGUIInfo() const
	{
		static const FeatureGUIInfo info{ "Asset Dump", "Settings", false };
		return info;
	}

	void AssetDump::DrawMain()
	{
		ImGui::BeginGroupPanel("Asset Dump");
		{
			ConfigWidget(f_Enabled, "Dump asset path");
		}
		ImGui::EndGroupPanel();
	}

	bool AssetDump::NeedStatusDraw() const
	{
		return f_Enabled;
	}

	void AssetDump::DrawStatus()
	{
		ImGui::Text("Asset Dump");
	}

	AssetDump& AssetDump::GetInstance()
	{
		static AssetDump instance;
		return instance;
	}

    static uint64_t CommonMiscs_GetAssetPathHash_1_Hook(app::String* path, app::String* extention, MethodInfo* method)
    {
		auto& ad = AssetDump::GetInstance();
        auto m_path = il2cppi_to_string(path);
        auto m_extension = il2cppi_to_string(extention);
        auto value = CALL_ORIGIN(CommonMiscs_GetAssetPathHash_1_Hook, path, extention, method);
        if (ad.f_Enabled && m_extension == ".MiHoYoBinData") {
            LOG_DEBUG("path: %s, hash: %x", m_path.c_str(), value);
        }
        return value;
    }
}
