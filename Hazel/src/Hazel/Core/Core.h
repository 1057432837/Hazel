#pragma once

#include "memory"

/*----------------------Windows----------------------*/
#ifdef _WIN32										//
	#ifdef _WIN64									//
		#define HZ_PLATFORM_WINDOWS					//
	#else											//
		#error "x86 Builds are not supported!"		//
	#endif											//
													//
/*--------------------Apple & Mac--------------------*/
#elif defined(__APPLE__) || defined(__MAC__)		//
	#include <TargetConditionals.h>					//
	#if TARGET_IPHONE_SIMULATOR == 1				//
		#error "IOS simulator is not supported!"	//
	#elif TARGET_OS_IPHONE == 1						//
		#define HZ_PLATFORM_IOS						//
		#error "IOS is not supported!"				//
	#elif TARGET_OS_MAC == 1						//
		#define HZ_PLATFORM_MACOS					//
		#error "MacOS is not supported!"			//
	#else											//
		#error "Unknown Apple platform!"			//
	#endif											//
													//
/*----------------------Android----------------------*/
#elif defined(__ANDROID__)							//
	#define HZ_PLATFORM_ANDROID						//
	#error "Android is not supported!"				//
													//
/*-----------------------Linux-----------------------*/
#elif defined(__LINUX__)							//
	#define HZ_PLATFORM_LINUX						//
	#error "Linux is not supported!"				//
													//
/*----------------------Unknown----------------------*/
#else												//
	#error "Unknown platform!"						//
													//
#endif												//
													//
/*---------------------------------------------------*/

/*----------------Windows DLL support----------------*/
#ifdef HZ_PLATFORM_WINDOWS							//
	#if HZ_DYNAMIC_LINK								//
		#ifdef HZ_BUILD_DLL							//
			#define HAZEL_API __declspec(dllexport)	//
		#else										//
			#define HAZEL_API __declspec(dllimport)	//
		#endif										//
	#else											//
		#define HAZEL_API							//
#endif												//
#else												//
	#error Hazel only supports Windows!				//
#endif												//
													//
/*---------------------------------------------------*/

#ifdef HZ_ENABLE_ASSERTS
	#define HZ_ASSERT(x, ...) { if(!(x)) {HZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
	#define HZ_CORE_ASSERT(x, ...) { if(!(x)) {HZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#else
	#define HZ_ASSERT(x, ...)
	#define HZ_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define HZ_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Hazel {
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

	template <typename T, typename... Args>
	constexpr Scope<T> CreateScope(Args&&... args) {
		return std::make_unique<T>(std::forward<Args>(args)...);

	}

	template <typename T, typename... Args>
	constexpr Ref<T> CreateRef(Args&&... args) {
		return std::make_shared<T>(std::forward<Args>(args)...);

	}

	template <typename T2, typename T1>
	Ref<T2> Cast(Ref<T1> const& ptr) {
		return std::dynamic_pointer_cast<T2>(ptr);

	}

}