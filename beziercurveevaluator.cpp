#include "beziercurveevaluator.h"
#include "mat.h"
#include "vec.h"


void BezierCurveEvaluator::evaluateCurve(const std::vector<Point>& ptvCtrlPts,
	std::vector<Point>& ptvEvaluatedCurvePts,
	const float & fAniLength,
	const bool & bWrap) const
{
	ptvEvaluatedCurvePts.clear();

	int iCtrlPtCount = ptvCtrlPts.size();

	 Mat4d Mb(
		-1, 3, -3, 1,
		3, -6, 3, 0,
		-3, 3, 0, 0,
		1, 0, 0, 0
	);

	int count;
	for (count = 0; count + 3 < iCtrlPtCount; count += 3) {
		ptvEvaluatedCurvePts.push_back(ptvCtrlPts[count]);
		ptvEvaluatedCurvePts.push_back(ptvCtrlPts[count + 3]);
		 Vec4d px(ptvCtrlPts[count].x, ptvCtrlPts[count + 1].x, ptvCtrlPts[count + 2].x, ptvCtrlPts[count + 3].x);
		 Vec4d py(ptvCtrlPts[count].y, ptvCtrlPts[count + 1].y, ptvCtrlPts[count + 2].y, ptvCtrlPts[count + 3].y);

		for (int i = 0; i < 30; ++i) {
			const double t = i / 30.0;
			const Vec4d pt(t*t*t, t*t, t, 1.0);
			
			ptvEvaluatedCurvePts.push_back(Point(pt * Mb * px, pt * Mb * py));
		}
	}

	ptvEvaluatedCurvePts.push_back(Point(0.0, ptvCtrlPts[0].y));

	for (; count < iCtrlPtCount; count++) {
		ptvEvaluatedCurvePts.push_back(ptvCtrlPts[count]);
	}

	ptvEvaluatedCurvePts.push_back(Point(fAniLength, ptvCtrlPts[count-1].y));
}
