#include "../moneyhack.hpp"
#include <numbers>
#include <cmath>
#define M_PI 3.14159265358979323846264338327950288419716939937510
static ULONG ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
static ULONG ScreenHeight = GetSystemMetrics(SM_CYSCREEN);

int screenWidth = GetSystemMetrics(SM_CXSCREEN);
int screenHeight = GetSystemMetrics(SM_CYSCREEN);
#include <assert.h>
#define IM_ASSERT(_EXPR)            assert(_EXPR)  

namespace structs
{
	struct ImVec2
	{
		float                                   x, y;
		constexpr ImVec2() : x(0.0f), y(0.0f) { }
		constexpr ImVec2(float _x, float _y) : x(_x), y(_y) { }
		float& operator[] (size_t idx) { IM_ASSERT(idx == 0 || idx == 1); return ((float*)(void*)(char*)this)[idx]; } // We very rarely use this [] operator, so the assert overhead is fine.
		float  operator[] (size_t idx) const { IM_ASSERT(idx == 0 || idx == 1); return ((const float*)(const void*)(const char*)this)[idx]; }
#ifdef IM_VEC2_CLASS_EXTRA
		IM_VEC2_CLASS_EXTRA     // Define additional constructors and implicit cast operators in imconfig.h to convert back and forth between your math types and ImVec2.
#endif
	};

	// ImVec4: 4D vector used to store clipping rectangles, colors etc. [Compile-time configurable type]
	struct ImVec4
	{
		float                                                     x, y, z, w;
		constexpr ImVec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) { }
		constexpr ImVec4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) { }
#ifdef IM_VEC4_CLASS_EXTRA
		IM_VEC4_CLASS_EXTRA     // Define additional constructors and implicit cast operators in imconfig.h to convert back and forth between your math types and ImVec4.
#endif
	};
	struct VIEW_MATRIX_MONEY {
		float* operator[ ](int index) {
			return matrix[index];
		}

		float matrix[4][4];
	};
	class Vec2
	{
	public:
		float x, y;
	public:
		Vec2() :x(0.f), y(0.f) {}
		Vec2(float x_, float y_) :x(x_), y(y_) {}
		Vec2(ImVec2 ImVec2_) :x(ImVec2_.x), y(ImVec2_.y) {}
		Vec2 operator=(ImVec2 ImVec2_)
		{
			x = ImVec2_.x;
			y = ImVec2_.y;
			return *this;
		}
		Vec2 operator+(Vec2 Vec2_)
		{
			return { x + Vec2_.x,y + Vec2_.y };
		}
		Vec2 operator-(Vec2 Vec2_)
		{
			return { x - Vec2_.x,y - Vec2_.y };
		}
		Vec2 operator*(Vec2 Vec2_)
		{
			return { x * Vec2_.x,y * Vec2_.y };
		}
		Vec2 operator/(Vec2 Vec2_)
		{
			return { x / Vec2_.x,y / Vec2_.y };
		}
		Vec2 operator*(float n)
		{
			return { x / n,y / n };
		}
		Vec2 operator/(float n)
		{
			return { x / n,y / n };
		}
		bool operator==(Vec2 Vec2_)
		{
			return x == Vec2_.x && y == Vec2_.y;
		}
		bool operator!=(Vec2 Vec2_)
		{
			return x != Vec2_.x || y != Vec2_.y;
		}
		ImVec2 ToImVec2()
		{
			return ImVec2(x, y);
		}
		float Length()
		{
			return sqrtf(powf(x, 2) + powf(y, 2));
		}
		float DistanceTo(const Vec2& Pos)
		{
			return sqrtf(powf(Pos.x - x, 2) + powf(Pos.y - y, 2));
		}
	};
	struct Vector3
	{
		// constructor
		constexpr Vector3(
			const float x = 0.f,
			const float y = 0.f,
			const float z = 0.f) noexcept :
			x(x), y(y), z(z) { }

		// operator overloads
		constexpr const Vector3& operator-(const Vector3& other) const noexcept
		{
			return Vector3{ x - other.x, y - other.y, z - other.z };
		}

		constexpr const Vector3& operator+(const Vector3& other) const noexcept
		{
			return Vector3{ x + other.x, y + other.y, z + other.z };
		}

		constexpr const Vector3& operator/(const float factor) const noexcept
		{
			return Vector3{ x / factor, y / factor, z / factor };
		}

		constexpr const Vector3& operator*(const float factor) const noexcept
		{
			return Vector3{ x * factor, y * factor, z * factor };
		}

		constexpr const bool operator>(const Vector3& other) const noexcept {
			return x > other.x && y > other.y && z > other.z;
		}

		constexpr const bool operator>=(const Vector3& other) const noexcept {
			return x >= other.x && y >= other.y && z >= other.z;
		}

		constexpr const bool operator<(const Vector3& other) const noexcept {
			return x < other.x && y < other.y && z < other.z;
		}

		constexpr const bool operator<=(const Vector3& other) const noexcept {
			return x <= other.x && y <= other.y && z <= other.z;
		}


		float length() const {
			return std::sqrt(x * x + y * y + z * z);
		}

		float length2d() const {
			return std::sqrt(x * x + y * y);
		}

		constexpr const bool IsZero() const noexcept
		{
			return x == 0.f && y == 0.f && z == 0.f;
		}


		Vector3 world_to_screen(VIEW_MATRIX_MONEY matrix) const {
			float _x = matrix[0][0] * x + matrix[0][1] * y + matrix[0][2] * z + matrix[0][3];
			float _y = matrix[1][0] * x + matrix[1][1] * y + matrix[1][2] * z + matrix[1][3];

			float w = matrix[3][0] * x + matrix[3][1] * y + matrix[3][2] * z + matrix[3][3];

			float inv_w = 1.f / w;
			_x *= inv_w;
			_y *= inv_w;

			// Check the values at this point
			//std::cout << "_x: " << _x << ", _y: " << _y << ", w: " << w << std::endl;
			float screen_x = screenWidth * 0.5f;
			float screen_y = screenHeight * 0.5f;

			screen_x += 0.5f * _x * screenWidth + 0.5f;
			screen_y -= 0.5f * _y * screenHeight + 0.5f;

			// Check the final screen coordinates
			//std::cout << "screen_x: " << screen_x << ", screen_y: " << screen_y << std::endl;

			return { screen_x, screen_y, w };
		}


		// struct data
		float x, y, z;
	};

	// struct data
	float x, y, z;
};
