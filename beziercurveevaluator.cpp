#include "beziercurveevaluator.h"

void BezierCurveEvaluator::evaluateCurve(const std::vector<Point>& ptvCtrlPts,
	std::vector<Point>& ptvEvaluatedCurvePts,
	const float & fAniLength,
	const bool & bWrap) const
{
	ptvEvaluatedCurvePts.clear();
	
	vector<Point> ptvCtrlPtsCpy(ptvCtrlPts);
	if (bWrap) {
		ptvCtrlPtsCpy.push_back(Point(ptvCtrlPts.front().x + fAniLength, ptvCtrlPts.front().y));
	}

	int count;
	const Mat4d Mb(
		-1, 3, -3, 1,
		3, -6, 3, 0,
		-3, 3, 0, 0,
		1, 0, 0, 0
	);
	bool is_wrapped = false;

	for (count = 0; count + 3 < ptvCtrlPtsCpy.size(); count += 3) {
		ptvEvaluatedCurvePts.push_back(ptvCtrlPtsCpy[count]);
		ptvEvaluatedCurvePts.push_back(ptvCtrlPtsCpy[count + 3]);
		const Vec4d px(ptvCtrlPtsCpy[count].x, ptvCtrlPtsCpy[count + 1].x, ptvCtrlPtsCpy[count + 2].x, ptvCtrlPtsCpy[count + 3].x);
		const Vec4d py(ptvCtrlPtsCpy[count].y, ptvCtrlPtsCpy[count + 1].y, ptvCtrlPtsCpy[count + 2].y, ptvCtrlPtsCpy[count + 3].y);

		for (int i = 0; i < 30; ++i) {
			const double t = i / 30.0;
			const Vec4d pt(t*t*t, t*t, t, 1.0);
			Point Qt(pt * Mb * px, pt * Mb * py);
			if (Qt.x > fAniLength && bWrap)
			{
				const float x_mod = fmod(Qt.x, fAniLength);
				if (!is_wrapped)
				{
					const Point prev_point(ptvEvaluatedCurvePts.back());
					const float x_neg1 = prev_point.x - fAniLength;
					ptvEvaluatedCurvePts.push_back(Point(x_neg1, prev_point.y));
					ptvEvaluatedCurvePts.push_back(Qt);
					is_wrapped = true;
				}
				Qt.x = x_mod;
			}
			ptvEvaluatedCurvePts.push_back(Qt);
		}
	}


	for (; count < ptvCtrlPts.size(); count++) {
		ptvEvaluatedCurvePts.push_back(ptvCtrlPts[count]);
	}
	if (!bWrap) {
		ptvEvaluatedCurvePts.push_back(Point(0.0, ptvCtrlPts.front().y));
		ptvEvaluatedCurvePts.push_back(Point(fAniLength, ptvCtrlPts.back().y));
	}
	else if (!is_wrapped) {
		const float interval_length = ptvCtrlPts.front().x + fAniLength - ptvCtrlPts.back().x;
		const float percent = 1.0f - ptvCtrlPts.front().x / interval_length;
		const float y = ptvCtrlPts.back().y + (ptvCtrlPts.front().y - ptvCtrlPts.back().y) * percent;
		ptvEvaluatedCurvePts.push_back(Point(fAniLength, y));
		ptvEvaluatedCurvePts.push_back(Point(0.0f, y));
	}
}
