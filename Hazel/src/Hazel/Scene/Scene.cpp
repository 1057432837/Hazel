#include "hzpch.h"

#include "glm/glm.hpp"

#include "Scene.h"
#include "Hazel/Renderer/Renderer.h"
#include "Components.h"
#include "Hazel/Renderer/Renderer2D.h"
#include "Entity.h"

namespace Hazel {
	static void DoMath(const glm::mat4& transform) {

	}

	static void OnTransformConstruct(entt::registry& registry, entt::entity entity) {

	}

	Scene::Scene() {
#if ENTT_EXAMPLE_CODE
		entt::entity entity = m_Registry.create();
		m_Registry.emplace<TransformComponent>(entity, glm::mat4(1.0f));
		m_Registry.on_construct<TransformComponent>().connect<&OnTransformConstruct>();

		if (m_Registry.all_of<TransformComponent>(entity))
		{
			TransformComponent& transform = m_Registry.get<TransformComponent>(entity);

		}
		
		auto view = m_Registry.view<TransformComponent>();
		for (auto entity : view)
		{
			TransformComponent& transform = view.get<TransformComponent>(entity);

		}

		auto group = m_Registry.group<TransformComponent>(entt::get<MeshComponent>);

		for (auto entity : group)
		{
			auto&[transform, mesh] = group.get<TransformComponent, MeshComponent>(entity);

		}

#endif

	}

	Scene::~Scene() {

	}

	void Scene::OnUpdate(Timestep ts) {
		{
			m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
				{
					if (!nsc.Instance)
					{
						nsc.Instance = nsc.InstantiateScript();
						nsc.Instance->m_Entity = Entity{ entity, this };
						nsc.Instance->OnCreate();

					}

					nsc.Instance->OnUpdate(ts);

				});

		}

		Camera* mainCamera = nullptr;
		glm::mat4 cameraTransform;

		{
			auto view = m_Registry.view<TransformComponent, CameraComponent>();
			for (auto entity : view)
			{
				auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);

				if (camera.Primary)
				{
					mainCamera = &camera.Camera;
					cameraTransform = transform.GetTransform();
					break;

				}

			}

		}

		if (mainCamera)
		{
			Renderer2D::BeginScene(mainCamera->GetProjection(), cameraTransform);

			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);

			for (auto entity : group)
			{
				auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

				Renderer2D::DrawQuad(transform.GetTransform(), sprite.Color);

			}

			Renderer2D::EndScene();

		}

	}

	void Scene::OnViewportResize(uint32_t width, uint32_t height) {
		m_ViewportWidth = width;
		m_ViewportHeight = height;

		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view) {
			auto& cameraComponent = view.get<CameraComponent>(entity);
			if (!cameraComponent.FixedAspectRatio)
			{
				cameraComponent.Camera.SetViewportSize(width, height);
			
			}

		}

	}

	bool Scene::IsEntityValid(entt::entity entity) const {
		return m_Registry.valid(entity);

	}

	Ref<Scene> Scene::Create() {
		return CreateRef<Scene>();

	}

	Ref<Entity> Scene::CreateEntity(const std::string& name) {
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity" : name;

		return CreateRef<Entity>(entity);

	}

	void Scene::DestroyEntity(Entity entity) {
		m_Registry.destroy(entity);

	}

	template<typename T>
	void Scene::OnComponentAdded(Entity entity, T& component) {
		static_assert(false);

	}

	template<>
	void Scene::OnComponentAdded<TransformComponent>(Entity entity, TransformComponent& component) {

	}

	template<>
	void Scene::OnComponentAdded<CameraComponent>(Entity entity, CameraComponent& component) {
		component.Camera.SetViewportSize(m_ViewportWidth, m_ViewportHeight);

	}

	template<>
	void Scene::OnComponentAdded<SpriteRendererComponent>(Entity entity, SpriteRendererComponent& component) {

	}

	template<>
	void Scene::OnComponentAdded<TagComponent>(Entity entity, TagComponent& component) {

	}

	template<>
	void Scene::OnComponentAdded<NativeScriptComponent>(Entity entity, NativeScriptComponent& component) {

	}

}