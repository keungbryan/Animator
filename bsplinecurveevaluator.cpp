#include "bsplinecurveevaluator.h"
#include "beziercurveevaluator.h"
#include <assert.h>
#include "mat.h"
#include "vec.h"

void BSplineCurveEvaluator::evaluateCurve(const std::vector<Point>& ptvCtrlPts, 
										  std::vector<Point>& ptvEvaluatedCurvePts, 
										  const float & fAniLength, 
										  const bool & bWrap) const
{
	ptvEvaluatedCurvePts.clear();

	Point start1, start2, end1, end2;
	
	vector<Point> ptvCtrlPtsCpy;
	if (bWrap) {
		start1 = Point((ptvCtrlPts.end() - 2)->x -fAniLength, (ptvCtrlPts.end() - 2)->y);
		start2 = Point((ptvCtrlPts.end() - 1)->x - fAniLength, (ptvCtrlPts.end() - 1)->y);
		end1 = Point((ptvCtrlPts.begin())->x + fAniLength, (ptvCtrlPts.begin())->y);
		end2 = Point((ptvCtrlPts.begin()+1)->x + fAniLength, (ptvCtrlPts.begin()+1)->y);
	}
	else {
		ptvEvaluatedCurvePts.push_back(Point(0.0, ptvCtrlPts.front().y));
		ptvEvaluatedCurvePts.push_back(Point(fAniLength, ptvCtrlPts.back().y));
		start1 = ptvCtrlPts.front();
		start2 = ptvCtrlPts.front();
		end1 = ptvCtrlPts.back();
		end2 = ptvCtrlPts.back();
	}

	ptvCtrlPtsCpy.push_back(start1);
	ptvCtrlPtsCpy.push_back(start2);
	ptvCtrlPtsCpy.insert(ptvCtrlPtsCpy.end(), ptvCtrlPts.begin(), ptvCtrlPts.end());
	ptvCtrlPtsCpy.push_back(end1);
	ptvCtrlPtsCpy.push_back(end2);

	BezierCurveEvaluator bezierCurveEvaluator;

	int iCtrlPtCount = ptvCtrlPtsCpy.size();
	 
	const Mat4d Mb = Mat4d(
		1, 4, 1, 0,
		0, 4, 2, 0,
		0, 2, 4, 0,
		0, 1, 4, 1
		) /6.0;
	for (int count = 0; count + 3 < iCtrlPtCount; ++count) {
		Vec4d px(ptvCtrlPtsCpy[count].x, ptvCtrlPtsCpy[count + 1].x, ptvCtrlPtsCpy[count + 2].x, ptvCtrlPtsCpy[count + 3].x);
		Vec4d py(ptvCtrlPtsCpy[count].y, ptvCtrlPtsCpy[count + 1].y, ptvCtrlPtsCpy[count + 2].y, ptvCtrlPtsCpy[count + 3].y);
		px = Mb * px;
		py = Mb * py;
		vector<Point> bezierControl;
		for (int i = 0; i < 4; ++i) {
			bezierControl.push_back(Point(px[i], py[i]));
		}
		vector<Point> bezierEvaluated;
		bezierCurveEvaluator.evaluateCurve(bezierControl, bezierEvaluated, fAniLength, false);
		ptvEvaluatedCurvePts.insert(ptvEvaluatedCurvePts.end(), bezierEvaluated.begin(), bezierEvaluated.end()-2);
	}
}
