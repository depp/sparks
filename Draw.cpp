/****************************************************/
/*                     Headers                      */
/****************************************************/

#include "Entity.h"
#include "Header.h"
#include "Vectors.h"
#include "Viewpoint.h"

/****************************************************/
/*                    Main Code                     */
/****************************************************/

static int Rects_Intersect(Rect *r, Rect *s) {
	return ((r->bottom > s->top) && (r->top < s->bottom) &&
	        (r->right > s->left) && (r->left < s->right));
}

static inline void Fix_Rect(Rect *r) {
	short temp;

	if (r->bottom < r->top) {
		temp = r->bottom;
		r->bottom = r->top;
		r->top = temp;
	}
	if (r->right < r->left) {
		temp = r->right;
		r->right = r->left;
		r->left = temp;
	}
}

int Clip_Rect(t_Vector2f corner1, t_Vector2f corner2) {
	Rect R;

	*((Point *)(&R)) = Viewpoint_Transform(corner1);
	*((Point *)(&R) + 1) = Viewpoint_Transform(corner2);
	Fix_Rect(&R);

	return !Rects_Intersect(&R, &gBufferRect);
}

int Clip_Circle(t_Vector2f center, float r) {
	t_Vector2f v1(r, -r), v2(-r, r);
	Rect R;

	v1 += center;
	v2 += center;

	*((Point *)(&R)) = Viewpoint_Transform(v1);
	*((Point *)(&R) + 1) = Viewpoint_Transform(v2);
	Fix_Rect(&R);

	return !Rects_Intersect(&R, &gBufferRect);
}

void Draw_Circle(t_Vector2f center, float r) {
	t_Vector2f v1(r, -r), v2(-r, r);
	Rect R;

	v1 += center;
	v2 += center;

	*((Point *)(&R)) = Viewpoint_Transform(v1);
	*((Point *)(&R) + 1) = Viewpoint_Transform(v2);
	Fix_Rect(&R);

	PaintOval(&R);
}

void Draw_Circle(t_Vector2f center, int r) {
	Rect R;

	*((Point *)(&R) + 1) = *((Point *)(&R)) = Viewpoint_Transform(center);

	R.top -= r;
	R.left -= r;
	R.bottom += r;
	R.right += r;

	PaintOval(&R);
}

void Draw_CircleOutline(t_Vector2f center, float r) {
	t_Vector2f v1(r, -r), v2(-r, r);
	Rect R;

	v1 += center;
	v2 += center;

	*((Point *)(&R)) = Viewpoint_Transform(v1);
	*((Point *)(&R) + 1) = Viewpoint_Transform(v2);
	Fix_Rect(&R);

	FrameOval(&R);
}

void Draw_CircleOutline(t_Vector2f center, int r) {
	Rect R;

	*((Point *)(&R) + 1) = *((Point *)(&R)) = Viewpoint_Transform(center);

	R.top -= r;
	R.left -= r;
	R.bottom += r;
	R.right += r;

	FrameOval(&R);
}

void Draw_Line(t_Vector2f start, t_Vector2f end) {
	Point p1, p2;

	p1 = Viewpoint_Transform(start);
	p2 = Viewpoint_Transform(end);

	MoveTo(p1.h, p1.v);
	LineTo(p2.h, p2.v);
}

void Draw_String_Centered(t_Vector2f loc, Str255 s) {
	Point p;

	p = Viewpoint_Transform(loc);
	p.h -= StringWidth(s) / 2;
	MoveTo(p.h, p.v);
	DrawString(s);
}

void Draw_Triangle(t_Vector2f a, t_Vector2f b, t_Vector2f c, UInt8 color) {
	Point l[3], r[3];
	short nl, nr;

	{
		Point pa, pb, pc, t;

		pa = Viewpoint_Transform(a);
		pb = Viewpoint_Transform(b);
		pc = Viewpoint_Transform(c);

		if (!(pa.v < pc.v)) {
			t = pa;
			pa = pc;
			pc = t;
		}
		if (!(pa.v < pb.v)) {
			t = pa;
			pa = pb;
			pb = t;
		}
		if (!(pb.v < pc.v)) {
			t = pb;
			pb = pc;
			pc = t;
		}

		if (pa.v == pb.v) {
			nl = nr = 2;
			l[1] = r[1] = pc;
			if (pa.h < pb.h) {
				l[0] = pa;
				r[0] = pb;
			} else {
				l[0] = pb;
				r[0] = pa;
			}
		} else {
			l[0] = r[0] = pa;
			if (pb.v == pc.v) {
				nl = nr = 2;
				if (pb.h < pc.h) {
					l[1] = pb;
					r[1] = pc;
				} else {
					l[1] = pc;
					r[1] = pb;
				}
			} else {
				if ((pb.h < pa.h) && (pb.h < pc.h)) {
					nl = 3;
					nr = 2;
					l[1] = pb;
					r[1] = l[2] = pc;
				} else if ((pb.h > pa.h) && (pb.h > pc.h)) {
					nr = 3;
					nl = 2;
					l[1] = r[2] = pc;
					r[1] = pb;
				} else {
					if (pb.h <
					    ((pb.v - pa.v) * (pc.h - pa.h)) / (pc.v - pa.v)) {
						nl = 3;
						nr = 2;
						l[1] = pb;
						r[1] = l[2] = pc;
					} else {
						nr = 3;
						nl = 2;
						l[1] = r[2] = pc;
						r[1] = pb;
					}
				}
			}
		}
	}

	{
		short left_HLoc;
		short left_HRem;
		short left_CurPoint;
		short left_DeltaH;
		short left_DeltaV;
		short left_Dir;
		short right_HLoc;
		short right_HRem;
		short right_CurPoint;
		short right_DeltaH;
		short right_DeltaV;
		short right_Dir;
		short VLoc;
		short HLoc;
		short lPos;
		short rPos;

		Boolean offscreen;

		Ptr curPtr;
		Ptr rowPtr;
		long bytesPerRow;

		VLoc = l[0].v;

		bytesPerRow = (**gPixMap).rowBytes & 0x7FFF;
		rowPtr = (**gPixMap).baseAddr + bytesPerRow * VLoc;

		left_CurPoint = 0;
		right_CurPoint = 0;

		while (VLoc <= l[nl - 1].v) {
			if (!(VLoc == l[nl - 1].v)) {
				if (VLoc == l[left_CurPoint].v) {
					left_HLoc = l[left_CurPoint].h;
					left_DeltaH = l[left_CurPoint + 1].h - l[left_CurPoint].h;
					left_DeltaV = l[left_CurPoint + 1].v - l[left_CurPoint].v;
					left_Dir =
						(left_DeltaH > 0) ? 1 : ((left_DeltaH < 0) ? -1 : 0);
					left_DeltaH *= left_Dir;
					left_CurPoint++;
					left_HRem = left_DeltaV / 2;
				} else {
					left_HRem += left_DeltaH;
					left_HLoc += (left_HRem / left_DeltaV) * left_Dir;
					left_HRem %= left_DeltaV;
				}
				if (VLoc == r[right_CurPoint].v) {
					right_HLoc = r[right_CurPoint].h;
					right_DeltaH =
						r[right_CurPoint + 1].h - r[right_CurPoint].h;
					right_DeltaV =
						r[right_CurPoint + 1].v - r[right_CurPoint].v;
					right_Dir =
						(right_DeltaH > 0) ? 1 : ((right_DeltaH < 0) ? -1 : 0);
					right_DeltaH *= right_Dir;
					right_CurPoint++;
					right_HRem = right_DeltaV / 2;
				} else {
					right_HRem += right_DeltaH;
					right_HLoc += (right_HRem / right_DeltaV) * right_Dir;
					right_HRem %= right_DeltaV;
				}
			} else {
				left_HLoc = l[nl - 1].h;
				right_HLoc = r[nr - 1].h;
			}

			offscreen = (VLoc < gBufferRect.top);
			if (VLoc > gBufferRect.bottom)
				return;

			if (!offscreen) {
				if (left_HLoc > gBufferRect.left) {
					if (left_HLoc < gBufferRect.right) {
						lPos = left_HLoc;
					} else {
						offscreen = true;
					}
				} else {
					lPos = gBufferRect.left;
				}
			}

			if (!offscreen) {
				if (right_HLoc > gBufferRect.left) {
					if (right_HLoc < gBufferRect.right) {
						rPos = right_HLoc;
					} else {
						rPos = gBufferRect.right;
					}
				} else {
					offscreen = true;
				}
			}

			if (!offscreen) {
				HLoc = lPos;
				curPtr = rowPtr + lPos;
				while (HLoc <= rPos) {
					*(UInt8 *)curPtr = color;

					curPtr++;
					HLoc++;
				}
			}

			VLoc++;
			rowPtr += bytesPerRow;
		}
	}
}

typedef struct {
	short v;
	short h;
	UInt8 c;
	UInt8 padding[3];
} coloredPoint;

void Draw_Triangle_Shaded(t_Vector2f *points, UInt8 *colors, UInt8 *gradTable) {
	coloredPoint l[3], r[3];
	short nl, nr;

	{
		coloredPoint pa, pb, pc, t;

		*((Point *)(&pa)) = Viewpoint_Transform(points[0]);
		*((Point *)(&pb)) = Viewpoint_Transform(points[1]);
		*((Point *)(&pc)) = Viewpoint_Transform(points[2]);

		pa.c = colors[0];
		pb.c = colors[1];
		pc.c = colors[2];

		if (!(pa.v < pc.v)) {
			t = pa;
			pa = pc;
			pc = t;
		}
		if (!(pa.v < pb.v)) {
			t = pa;
			pa = pb;
			pb = t;
		}
		if (!(pb.v < pc.v)) {
			t = pb;
			pb = pc;
			pc = t;
		}

		if (pa.v == pb.v) {
			nl = nr = 2;
			l[1] = r[1] = pc;
			if (pa.h < pb.h) {
				l[0] = pa;
				r[0] = pb;
			} else {
				l[0] = pb;
				r[0] = pa;
			}
		} else {
			l[0] = r[0] = pa;
			if (pb.v == pc.v) {
				nl = nr = 2;
				if (pb.h < pc.h) {
					l[1] = pb;
					r[1] = pc;
				} else {
					l[1] = pc;
					r[1] = pb;
				}
			} else {
				if ((pb.h < pa.h) && (pb.h < pc.h)) {
					nl = 3;
					nr = 2;
					l[1] = pb;
					r[1] = l[2] = pc;
				} else if ((pb.h > pa.h) && (pb.h > pc.h)) {
					nr = 3;
					nl = 2;
					l[1] = r[2] = pc;
					r[1] = pb;
				} else {
					if (pb.h <
					    ((pb.v - pa.v) * (pc.h - pa.h)) / (pc.v - pa.v)) {
						nl = 3;
						nr = 2;
						l[1] = pb;
						r[1] = l[2] = pc;
					} else {
						nr = 3;
						nl = 2;
						l[1] = r[2] = pc;
						r[1] = pb;
					}
				}
			}
		}
	}

	{
		short left_HLoc;
		short left_HRem;
		short left_CurPoint;
		short left_DeltaH;
		short left_DeltaV;
		short left_HDir;

		short right_HLoc;
		short right_HRem;
		short right_CurPoint;
		short right_DeltaH;
		short right_DeltaV;
		short right_HDir;

		short left_DeltaC;
		short left_Color;
		short left_CRem;
		short left_CDir;

		short right_DeltaC;
		short right_Color;
		short right_CRem;
		short right_CDir;

		short color;
		short colorRem;
		short deltaColor;
		short deltaH;

		short VLoc;
		short HLoc;
		short lPos;
		short rPos;

		Boolean offscreen;

		Ptr curPtr;
		Ptr rowPtr;
		long bytesPerRow;

		VLoc = l[0].v;

		bytesPerRow = (**gPixMap).rowBytes & 0x7FFF;
		rowPtr = (**gPixMap).baseAddr + bytesPerRow * VLoc;

		left_CurPoint = 0;
		right_CurPoint = 0;

		while (VLoc <= l[nl - 1].v) {
			if (!(VLoc == l[nl - 1].v)) {
				if (VLoc == l[left_CurPoint].v) {
					left_DeltaV = l[left_CurPoint + 1].v - l[left_CurPoint].v;

					left_HLoc = l[left_CurPoint].h;
					left_DeltaH = l[left_CurPoint + 1].h - l[left_CurPoint].h;
					left_HDir =
						(left_DeltaH > 0) ? 1 : ((left_DeltaH < 0) ? -1 : 0);
					left_DeltaH *= left_HDir;
					left_HRem = left_DeltaV / 2;

					left_Color = l[left_CurPoint].c;
					left_DeltaC = l[left_CurPoint + 1].c - l[left_CurPoint].c;
					left_CRem = left_DeltaV / 2;
					left_CDir =
						(left_DeltaC > 0) ? 1 : ((left_DeltaC < 0) ? -1 : 0);
					left_DeltaC *= left_CDir;

					left_CurPoint++;
				} else {
					left_HRem += left_DeltaH;
					left_HLoc += (left_HRem / left_DeltaV) * left_HDir;
					left_HRem %= left_DeltaV;

					left_CRem += left_DeltaC;
					left_Color += (left_CRem / left_DeltaV) * left_CDir;
					;
					left_CRem %= left_DeltaV;
				}
				if (VLoc == r[right_CurPoint].v) {
					right_DeltaV =
						r[right_CurPoint + 1].v - r[right_CurPoint].v;

					right_HLoc = r[right_CurPoint].h;
					right_DeltaH =
						r[right_CurPoint + 1].h - r[right_CurPoint].h;
					right_HDir =
						(right_DeltaH > 0) ? 1 : ((right_DeltaH < 0) ? -1 : 0);
					right_DeltaH *= right_HDir;
					right_HRem = right_DeltaV / 2;

					right_Color = r[right_CurPoint].c;
					right_DeltaC =
						r[right_CurPoint + 1].c - r[right_CurPoint].c;
					right_CRem = right_DeltaV / 2;
					right_CDir =
						(right_DeltaC > 0) ? 1 : ((right_DeltaC < 0) ? -1 : 0);
					right_DeltaC *= right_CDir;

					right_CurPoint++;
				} else {
					right_HRem += right_DeltaH;
					right_HLoc += (right_HRem / right_DeltaV) * right_HDir;
					right_HRem %= right_DeltaV;

					right_CRem += right_DeltaC;
					right_Color += (right_CRem / right_DeltaV) * right_CDir;
					right_CRem %= right_DeltaV;
				}
			} else {
				left_HLoc = l[nl - 1].h;
				left_Color = l[nl - 1].c;
				right_HLoc = r[nr - 1].h;
				right_Color = r[nr - 1].c;
			}

			offscreen = (VLoc < gBufferRect.top);
			if (VLoc > gBufferRect.bottom)
				return;

			if (!offscreen) {
				if (left_HLoc > gBufferRect.left) {
					if (left_HLoc < gBufferRect.right) {
						lPos = left_HLoc;
					} else {
						offscreen = true;
					}
				} else {
					lPos = gBufferRect.left;
				}
			}

			if (!offscreen) {
				if (right_HLoc > gBufferRect.left) {
					if (right_HLoc < gBufferRect.right) {
						rPos = right_HLoc;
					} else {
						rPos = gBufferRect.right;
					}
				} else {
					offscreen = true;
				}
			}

			if (!offscreen) {
				deltaH = right_HLoc - left_HLoc + 1;
				color = left_Color;
				deltaColor = right_Color - left_Color;
				colorRem = deltaH / 2 + (lPos - left_HLoc) * deltaColor;

				color += (colorRem / deltaH);
				colorRem %= deltaH;

				HLoc = lPos;
				curPtr = rowPtr + lPos;
				while (HLoc <= rPos) {
					*(UInt8 *)curPtr = gradTable[color];

					colorRem += deltaColor;
					color += (colorRem / deltaH);
					colorRem %= deltaH;

					curPtr++;
					HLoc++;
				}
			}

			VLoc++;
			rowPtr += bytesPerRow;
		}
	}
}
