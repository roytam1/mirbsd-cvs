/*
 * header file for transformed coordinate system.  No rotations
 * supported, as elipses cannot be rotated in X.
 */
/* $XFree86: xc/programs/xeyes/transform.h,v 1.3 2000/02/17 14:00:35 dawes Exp $ */

typedef struct _transform {
	double	mx, bx;
	double	my, by;
} Transform;

typedef struct _TPoint {
	double	x, y;
} TPoint;

typedef struct _TRectangle {
	double	x, y, width, height;
} TRectangle;

# define Xx(x,y,t)	((int)((t)->mx * (x) + (t)->bx + 0.5))
# define Xy(x,y,t)	((int)((t)->my * (y) + (t)->by + 0.5))
# define Xwidth(w,h,t)	((int)((t)->mx * (w) + 0.5))
# define Xheight(w,h,t)	((int)((t)->my * (h) + 0.5))
# define Tx(x,y,t)	((((double) (x)) - (t)->bx) / (t)->mx)
# define Ty(x,y,t)	((((double) (y)) - (t)->by) / (t)->my)
# define Twidth(w,h,t)	(((double) (w)) / (t)->mx)
# define Theight(w,h,t)	(((double) (h)) / (t)->my)

extern void TFillArc (Display *dpy, Drawable d, GC gc,
                      Transform *t,
                      double x, double y, double width, double height,
                      int angle1, int angle2);
extern void SetTransform (Transform *t,
                          int xx1, int xx2, int xy1, int xy2,
                          double tx1, double tx2, double ty1, double ty2);
