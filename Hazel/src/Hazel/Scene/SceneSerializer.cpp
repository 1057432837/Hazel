#include "hzpch.h"
#include "fstream"

#define YAML_CPP_STATIC_DEFINE
#include "yaml-cpp/yaml.h"

#include "SceneSerializer.h"
#include "Entity.h"
#include "Components.h"

namespace Hazel {
	SceneSerializer::SceneSerializer() {

	}

	SceneSerializer::~SceneSerializer() {

	}

	SceneSerializer::SceneSerializer(const Ref<Scene>& scene) : m_Scene(scene) {

	}

	static void SerializeEntity(YAML::Emitter& out, Entity entity) {
		out << YAML::BeginMap;
		out << YAML::Key << "Entity" << YAML::Value << (uint32_t)(entity);

		if (entity.HasComponent<TagComponent>())
		{
			out << YAML::Key << "TagComponent";
			out << YAML::BeginMap; // TagComponent

			auto& tag = entity.GetComponent<TagComponent>().Tag;
			out << YAML::Key << "Tag" << YAML::Value << tag;

			out << YAML::EndMap; // TagComponent

		}

		out << YAML::EndMap;

	}

	void SceneSerializer::Serialize(const std::string& filepath) {
		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "Scene" << YAML::Value << "Untitled";
		out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;
		m_Scene->m_Registry.view<entt::entity>().each([&](auto entityID)
			{
				Entity entity = { entityID, m_Scene.get() };
				if (!entity)
					return;

				SerializeEntity(out, entity);
			});
		out << YAML::EndSeq;
		out << YAML::EndMap;

		std::ofstream fout(filepath);
		fout << out.c_str();

	}

	void SceneSerializer::SerializeRuntime(const std::string& filepath) {
		HZ_CORE_ASSERT(false);

	}

	bool SceneSerializer::Deserialize(const std::string& filepath) {
		return false;

	}

	bool SceneSerializer::DeserializeRuntime(const std::string& filepath) {
		HZ_CORE_ASSERT(false);

		return false;

	}

}