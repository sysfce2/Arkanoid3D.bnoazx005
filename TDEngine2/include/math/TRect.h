/*!
	/file TRect.h
	/date 20.11.2018
	/authors Kasimov Ildar
*/

#pragma once


#include "../utils/Types.h"
#include "TVector2.h"
#include "MathUtils.h"
#include <tuple>
#include <array>
#include <algorithm>


namespace TDEngine2
{
	/*!
		struct TRect

		\brief The structure represents a 2D rectangle 

		         +----------------+ (x_max; y_max)
		         |                |
		         |                |
		  (x; y) +----------------+

		  where x_max = x + width, y_max = y + height
	*/

	template <typename T>
	struct TRect
	{
		T x, y, width, height;

		TDE2_API constexpr TRect() = default;
		TDE2_API constexpr TRect(const TRect&) = default;
		TDE2_API constexpr TRect(TRect&&) = default;

		TDE2_API constexpr TRect(T x, T y, T width, T height):
			x(x), y(y), width(width), height(height)
		{
		}

		TDE2_API TRect(const TVector2& leftBottom, const TVector2& rightTop):
			x(static_cast<T>(leftBottom.x)), y(static_cast<T>(leftBottom.y))
		{
			const TVector2 sizes = rightTop - leftBottom;

			width = static_cast<T>(std::abs(sizes.x));
			height = static_cast<T>(std::abs(sizes.y));
		}

		TDE2_API TRect& operator= (TRect<T> rect)
		{
			_swap(rect);
			return *this;
		}

		TDE2_API TVector2 GetLeftBottom() const { return TVector2(static_cast<F32>(x), static_cast<F32>(y)); }
		TDE2_API TVector2 GetRightTop() const { return TVector2(static_cast<F32>(x + width), static_cast<F32>(y + height)); }
		TDE2_API TVector2 GetSizes() const { return TVector2(static_cast<F32>(width), static_cast<F32>(height)); }

		TDE2_API std::array<TVector2, 4> GetPoints() const 
		{ 
			F32 x0 = static_cast<F32>(x);
			F32 y0 = static_cast<F32>(y);
			F32 x1 = static_cast<F32>(x + width);
			F32 y1 = static_cast<F32>(y + height);

			return 
			{
				TVector2(x0, y0),
				TVector2(x1, y0),
				TVector2(x1, y1),
				TVector2(x0, y1),
			};
		}

		protected:
			TDE2_API void _swap(TRect<T>& rect)
			{
				std::swap(x, rect.x);
				std::swap(y, rect.y);
				std::swap(width, rect.width);
				std::swap(height, rect.height);
			}
	};


	typedef TRect<F32> TRectF32;
	typedef TRect<U32> TRectU32;
	typedef TRect<I32> TRectI32;


	/*!
		\brief The operator implements an operation of translation a rectangle
		using an offset vector

		\param[in] rect A rectangle

		\param[in] translation Translation vector

		\return A new translated rectangle with the same sizes
	*/

	template <typename T>
	TRect<T> operator+ (const TRect<T>& rect, const TVector2& translation)
	{
		return { rect.x + translation.x, rect.y + translation.y, rect.width, rect.height };
	}


	template <typename T>
	bool operator== (const TRect<T>& leftRect, const TRect<T>& rightRect)
	{
		return (leftRect.x == rightRect.x) &&
				(leftRect.y == rightRect.y) &&
				(leftRect.width == rightRect.width) &&
				(leftRect.height == rightRect.height);
	}


	template <typename T>
	bool operator!= (const TRect<T>& leftRect, const TRect<T>& rightRect)
	{
		return (leftRect.x != rightRect.x) ||
				(leftRect.y != rightRect.y) ||
				(leftRect.width != rightRect.width) ||
				(leftRect.height != rightRect.height);
	}


	/*!
		\brief The function checks up whether a given point lies within a particular rect or not

		\note (the function's result is only correct when the Y axis of a given coordinate space
		is aligned upwards (0; 1)

		\param[in] rect A rectangle's object

		\param[in] point A 2d point

		\return true if a given point lies within a particular rect, false in other cases
	*/

	template <typename T>
	bool ContainsPoint(const TRect<T>& rect, const TVector2& point)
	{
		return (point.x > rect.x && point.x < (rect.x + rect.width) && point.y < (rect.y + rect.height) && point.y > rect.y);
	}


	/*!
		\brief The function checks up whether a given rect overlapes another rect

		\param[in] leftRect A first rect

		\param[in] rightRect A second rect

		\return Returns true if a given rect overlapes another rect
	*/

	template <typename T>
	bool IsOverlapped(const TRect<T>& leftRect, const TRect<T>& rightRect)
	{
		const F32 leftRectX2  = leftRect.x + leftRect.width;
		const F32 rightRectX2 = rightRect.x + rightRect.width;
		const F32 leftRectY2  = leftRect.y + leftRect.height;
		const F32 rightRectY2 = rightRect.y + rightRect.height;

		TRange<T> rx1(leftRect.x, leftRectX2);
		TRange<T> rx2(rightRect.x, rightRectX2);
		
		TRange<T> ry1(leftRect.y, leftRectY2);
		TRange<T> ry2(rightRect.y, rightRectY2);

		const bool isOverlappedXAxis = rx1.Contains(rightRect.x) || rx1.Contains(rightRectX2) || rx2.Contains(leftRect.x) || rx2.Contains(leftRectX2);
		const bool isOverlappedYAxis = ry1.Contains(rightRect.y) || ry1.Contains(rightRectY2) || ry2.Contains(leftRect.y) || ry2.Contains(leftRectY2);

		return isOverlappedXAxis && isOverlappedYAxis;
	}


	/*
		\brief The function converts a given point to normalized coordinates which are
		related to a given rectangle

		\param[in] rect A rectangle

		\param[in] point A 2d point

		\return A 2d point which has normalized coordinates relative to a given rectangle.
		If a given point lies outside of the rectangle the function returns a zero vector
	*/

	template <typename T>
	TVector2 PointToNormalizedCoords(const TRect<T>& rect, const TVector2& point, bool clampOutput = true)
	{
		TVector2 normalizedPoint { point.x - rect.x, point.y - rect.y };

		normalizedPoint.x /= rect.width;
		normalizedPoint.y /= rect.height;

		if (clampOutput) 
		{
			normalizedPoint.x = CMathUtils::Clamp01(normalizedPoint.x);
			normalizedPoint.y = CMathUtils::Clamp01(normalizedPoint.y);
		}

		return normalizedPoint;
	}

	
	/*!
		\brief The function splits a single rectangle in two based on a given cutting line

		\param[in] rect An original rectangle
		\param[in] pos A position should be normalized relatively to rectangle
		\param[in] isVertical A flag that defines a direction of spliting 

		\return A tuple which consists of two rectangles
	*/

	template <typename T>
	std::tuple<TRect<T>, TRect<T>> SplitRectWithLine(const TRect<T>& rect, const TVector2& pos, bool isVertical = false)
	{
		T ox = static_cast<T>(isVertical ? rect.x + pos.x : rect.x);
		T oy = static_cast<T>(isVertical ? rect.y : rect.y + pos.y);

		T firstRectWidth   = static_cast<T>(isVertical ? pos.x : rect.width);
		T firstRectHeight  = static_cast<T>(isVertical ? rect.height - pos.y : pos.y);
		T secondRectWidth  = static_cast<T>(isVertical ? rect.width - pos.x : rect.width);
		T secondRectHeight = static_cast<T>(isVertical ? rect.height : rect.height - pos.y);

		return { {rect.x, rect.y, firstRectWidth, firstRectHeight}, {ox, oy, secondRectWidth, secondRectHeight} };
	}


	template <typename T>
	TRect<T> MoveRect(const TRect<T>& rect, const TVector2& delta)
	{
		auto&& lbPoint = rect.GetLeftBottom() + delta;
		auto&& sizes = rect.GetSizes();

		return { lbPoint.x, lbPoint.y, sizes.x, sizes.y };
	}


	/*!
		\brief The method returns a new rectangle which is formed via intersection of two given rects.
		If there is no intersection a rectangle with zero sizes is returned
	*/

	template <typename T>
	TRect<T> IntersectRects(const TRect<T>& left, const TRect<T>& right)
	{
		if (!IsOverlapped(left, right))
		{
			return TRect<T>(0, 0, 0, 0);
		}

		const T x1 = std::min<T>(left.x + left.width, right.x + right.width);
		const T x2 = std::max<T>(left.x, right.x);
		const T y1 = std::min<T>(left.y + left.height, right.y + right.height);
		const T y2 = std::max<T>(left.y, right.y);

		return TRect<T>(std::min<T>(x1, x2), std::min<T>(y1, y2), std::max<T>(0.0f, x1 - x2), std::max<T>(0.0f, y1 - y2));

		//const T x1 = std::min<T>(left.x + left.width, right.x + right.width);
		//const T x2 = std::max<T>(left.x, right.x);
		//const T y1 = std::min<T>(left.y + left.height, right.y + right.height);
		//const T y2 = std::min<T>(left.y, right.y);

		//return TRect<T>(x2, y2, abs(x2 - x1), abs(y2 - y1));
	}
}
