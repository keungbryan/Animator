#include "catmullromcurveevaluator.h"

void CatmullRomCurveEvaluator::evaluateCurve(const std::vector<Point>& ptvCtrlPts,
	std::vector<Point>& ptvEvaluatedCurvePts,
	const float & fAniLength,
	const bool & bWrap) const
{
	ptvEvaluatedCurvePts.clear();

	vector<Point> ptvCtrlPtsCpy;
	if (bWrap) {
		Point start1((ptvCtrlPts.end() - 2)->x -fAniLength, (ptvCtrlPts.end() - 2)->y);
		Point start2((ptvCtrlPts.end() - 1)->x - fAniLength, (ptvCtrlPts.end() - 1)->y);
		Point end1((ptvCtrlPts.begin())->x + fAniLength, (ptvCtrlPts.begin())->y);
		Point end2((ptvCtrlPts.begin()+1)->x + fAniLength, (ptvCtrlPts.begin()+1)->y);
		ptvCtrlPtsCpy.push_back(start1);
		ptvCtrlPtsCpy.push_back(start2);
		ptvCtrlPtsCpy.insert(ptvCtrlPtsCpy.end(), ptvCtrlPts.begin(), ptvCtrlPts.end());
		ptvCtrlPtsCpy.push_back(end1);
		ptvCtrlPtsCpy.push_back(end2);
	}
	else {
		ptvCtrlPtsCpy.push_back(Point(0, ptvCtrlPts.front().y));
		ptvCtrlPtsCpy.insert(ptvCtrlPtsCpy.end(), ptvCtrlPts.begin(), ptvCtrlPts.end());
		ptvCtrlPtsCpy.push_back(Point(fAniLength, ptvCtrlPts.back().y));
	}

	int count;
	const Mat4d Mb = Mat4d(
		-1, 3, -3, 1,
		2, -5, 4, -1,
		-1, 0, 1, 0,
		0, 2, 0, 0)/2.0;

	for (count = 0; count + 3 < ptvCtrlPtsCpy.size(); ++count) {
		//ptvEvaluatedCurvePts.push_back(ptvCtrlPtsCpy[count]);
		//ptvEvaluatedCurvePts.push_back(ptvCtrlPtsCpy[count + 3]);
		const Vec4d px(ptvCtrlPtsCpy[count].x, ptvCtrlPtsCpy[count + 1].x, ptvCtrlPtsCpy[count + 2].x, ptvCtrlPtsCpy[count + 3].x);
		const Vec4d py(ptvCtrlPtsCpy[count].y, ptvCtrlPtsCpy[count + 1].y, ptvCtrlPtsCpy[count + 2].y, ptvCtrlPtsCpy[count + 3].y);

		for (int i = 0; i < 30; ++i) {
			const double t = i / 30.0;
			const Vec4d pt(t*t*t, t*t, t, 1.0);
			Point Qt(pt * Mb * px, pt * Mb * py);
			if (ptvEvaluatedCurvePts.empty() || Qt.x > ptvEvaluatedCurvePts.back().x) {
				ptvEvaluatedCurvePts.push_back(Qt);
			}		
		}
	}
	if (!bWrap) {
		ptvEvaluatedCurvePts.push_back(Point(0, ptvCtrlPts.front().y));
		ptvEvaluatedCurvePts.push_back(Point(fAniLength, ptvCtrlPts.back().y));
	}
}
