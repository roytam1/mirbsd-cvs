/* $NetBSD: t_sinh.c,v 1.4 2011/10/18 14:16:42 jruoho Exp $ */

/*-
 * Copyright (c) 2011 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Jukka Ruohonen.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#include <sys/cdefs.h>
__RCSID("$NetBSD: t_sinh.c,v 1.4 2011/10/18 14:16:42 jruoho Exp $");

#include <atf-c.h>
#include <math.h>
#include <stdio.h>

#define	__arraycount(__x)	(sizeof(__x) / sizeof(__x[0]))

/*
 * sinh(3)
 */
ATF_TC(sinh_def);
ATF_TC_HEAD(sinh_def, tc)
{
	atf_tc_set_md_var(tc, "descr", "Test the definition of sinh(3)");
}

ATF_TC_BODY(sinh_def, tc)
{
#ifndef __vax__
	const double x[] = { 0.005, 0.05, 0.0, 1.0, 10.0, 20.0 };
	const double eps = 1.0e-4;
	double y, z;
	size_t i;

	for (i = 0; i < __arraycount(x); i++) {

		y = sinh(x[i]);
		z = (exp(x[i]) - exp(-x[i])) / 2;

		(void)fprintf(stderr,
		    "sinh(%0.03f) = %f\n(exp(%0.03f) - "
		    "exp(-%0.03f)) / 2 = %f\n", x[i], y, x[i], x[i], z);

		if (fabs(y - z) > eps)
			atf_tc_fail_nonfatal("sinh(%0.03f) != %0.03f\n",
			    x[i], z);
	}
#endif
}

ATF_TC(sinh_nan);
ATF_TC_HEAD(sinh_nan, tc)
{
	atf_tc_set_md_var(tc, "descr", "Test sinh(NaN) == NaN");
}

ATF_TC_BODY(sinh_nan, tc)
{
#ifndef __vax__
	const double x = 0.0L / 0.0L;

	ATF_CHECK(isnan(x) != 0);
	ATF_CHECK(isnan(sinh(x)) != 0);
#endif
}

ATF_TC(sinh_inf_neg);
ATF_TC_HEAD(sinh_inf_neg, tc)
{
	atf_tc_set_md_var(tc, "descr", "Test sinh(-Inf) == -Inf");
}

ATF_TC_BODY(sinh_inf_neg, tc)
{
#ifndef __vax__
	const double x = -1.0L / 0.0L;
	double y = sinh(x);

	ATF_CHECK(isinf(y) != 0);
	ATF_CHECK(signbit(y) != 0);
#endif
}

ATF_TC(sinh_inf_pos);
ATF_TC_HEAD(sinh_inf_pos, tc)
{
	atf_tc_set_md_var(tc, "descr", "Test sinh(+Inf) == +Inf");
}

ATF_TC_BODY(sinh_inf_pos, tc)
{
#ifndef __vax__
	const double x = 1.0L / 0.0L;
	double y = sinh(x);

	ATF_CHECK(isinf(y) != 0);
	ATF_CHECK(signbit(y) == 0);
#endif
}

ATF_TC(sinh_zero_neg);
ATF_TC_HEAD(sinh_zero_neg, tc)
{
	atf_tc_set_md_var(tc, "descr", "Test sinh(-0.0) == -0.0");
}

ATF_TC_BODY(sinh_zero_neg, tc)
{
#ifndef __vax__
	const double x = -0.0L;
	double y = sinh(x);

	if (fabs(y) > 0.0 || signbit(y) == 0)
		atf_tc_fail_nonfatal("sinh(-0.0) != -0.0");
#endif
}

ATF_TC(sinh_zero_pos);
ATF_TC_HEAD(sinh_zero_pos, tc)
{
	atf_tc_set_md_var(tc, "descr", "Test sinh(+0.0) == +0.0");
}

ATF_TC_BODY(sinh_zero_pos, tc)
{
#ifndef __vax__
	const double x = 0.0L;
	double y = sinh(x);

	if (fabs(y) > 0.0 || signbit(y) != 0)
		atf_tc_fail_nonfatal("sinh(+0.0) != +0.0");
#endif
}

/*
 * sinhf(3)
 */
ATF_TC(sinhf_def);
ATF_TC_HEAD(sinhf_def, tc)
{
	atf_tc_set_md_var(tc, "descr", "Test the definition of sinhf(3)");
}

ATF_TC_BODY(sinhf_def, tc)
{
#ifndef __vax__
	const float x[] = { 0.005, 0.05, 0.0, 1.0, 10.0, 20.0 };
	const float eps = 1.0e-2;
	float y, z;
	size_t i;

	for (i = 0; i < __arraycount(x); i++) {

		y = sinhf(x[i]);
		z = (expf(x[i]) - expf(-x[i])) / 2;

		(void)fprintf(stderr,
		    "sinhf(%0.03f) = %f\n(expf(%0.03f) - "
		    "expf(-%0.03f)) / 2 = %f\n", x[i], y, x[i], x[i], z);

		if (fabsf(y - z) > eps)
			atf_tc_fail_nonfatal("sinhf(%0.03f) != %0.03f\n",
			    x[i], z);
	}
#endif
}

ATF_TC(sinhf_nan);
ATF_TC_HEAD(sinhf_nan, tc)
{
	atf_tc_set_md_var(tc, "descr", "Test sinhf(NaN) == NaN");
}

ATF_TC_BODY(sinhf_nan, tc)
{
#ifndef __vax__
	const float x = 0.0L / 0.0L;

	ATF_CHECK(isnan(x) != 0);
	ATF_CHECK(isnan(sinhf(x)) != 0);
#endif
}

ATF_TC(sinhf_inf_neg);
ATF_TC_HEAD(sinhf_inf_neg, tc)
{
	atf_tc_set_md_var(tc, "descr", "Test sinhf(-Inf) == -Inf");
}

ATF_TC_BODY(sinhf_inf_neg, tc)
{
#ifndef __vax__
	const float x = -1.0L / 0.0L;
	float y = sinhf(x);

	ATF_CHECK(isinf(y) != 0);
	ATF_CHECK(signbit(y) != 0);
#endif
}

ATF_TC(sinhf_inf_pos);
ATF_TC_HEAD(sinhf_inf_pos, tc)
{
	atf_tc_set_md_var(tc, "descr", "Test sinhf(+Inf) == +Inf");
}

ATF_TC_BODY(sinhf_inf_pos, tc)
{
#ifndef __vax__
	const float x = 1.0L / 0.0L;
	float y = sinhf(x);

	ATF_CHECK(isinf(y) != 0);
	ATF_CHECK(signbit(y) == 0);
#endif
}

ATF_TC(sinhf_zero_neg);
ATF_TC_HEAD(sinhf_zero_neg, tc)
{
	atf_tc_set_md_var(tc, "descr", "Test sinhf(-0.0) == -0.0");
}

ATF_TC_BODY(sinhf_zero_neg, tc)
{
#ifndef __vax__
	const float x = -0.0L;
	float y = sinhf(x);

	if (fabsf(y) > 0.0 || signbit(y) == 0)
		atf_tc_fail_nonfatal("sinhf(-0.0) != -0.0");
#endif
}

ATF_TC(sinhf_zero_pos);
ATF_TC_HEAD(sinhf_zero_pos, tc)
{
	atf_tc_set_md_var(tc, "descr", "Test sinhf(+0.0) == +0.0");
}

ATF_TC_BODY(sinhf_zero_pos, tc)
{
#ifndef __vax__
	const float x = 0.0L;
	float y = sinhf(x);

	if (fabsf(y) > 0.0 || signbit(y) != 0)
		atf_tc_fail_nonfatal("sinhf(+0.0) != +0.0");
#endif
}

ATF_TP_ADD_TCS(tp)
{

	ATF_TP_ADD_TC(tp, sinh_def);
	ATF_TP_ADD_TC(tp, sinh_nan);
	ATF_TP_ADD_TC(tp, sinh_inf_neg);
	ATF_TP_ADD_TC(tp, sinh_inf_pos);
	ATF_TP_ADD_TC(tp, sinh_zero_neg);
	ATF_TP_ADD_TC(tp, sinh_zero_pos);

	ATF_TP_ADD_TC(tp, sinhf_def);
	ATF_TP_ADD_TC(tp, sinhf_nan);
	ATF_TP_ADD_TC(tp, sinhf_inf_neg);
	ATF_TP_ADD_TC(tp, sinhf_inf_pos);
	ATF_TP_ADD_TC(tp, sinhf_zero_neg);
	ATF_TP_ADD_TC(tp, sinhf_zero_pos);

	return atf_no_error();
}
