/*-
 * Copyright © 2009, 2010
 *	Thorsten Glaser <t.glaser@tarent.de>
 *
 * Provided that these terms and disclaimer and all copyright notices
 * are retained or reproduced in an accompanying document, permission
 * is granted to deal in this work without restriction, including un‐
 * limited rights to use, publicly perform, distribute, sell, modify,
 * merge, give away, or sublicence.
 *
 * This work is provided “AS IS” and WITHOUT WARRANTY of any kind, to
 * the utmost extent permitted by applicable law, neither express nor
 * implied; without malicious intent or gross negligence. In no event
 * may a licensor, author or contributor be held liable for indirect,
 * direct, other damage, loss, or other issues arising in any way out
 * of dealing in the work, even if advised of the possibility of such
 * damage or existence of a defect, except proven that it results out
 * of said person’s immediate fault when using the work as intended.
 *-
 * KWallet interface file for Qt 3 and KDE 3
 */

#include <qstring.h>
#include <kaboutdata.h>
#include <kapplication.h>
#include <kcmdlineargs.h>
#include <kwallet.h>

#include "kwalletcli.h"

extern "C" char *getenv(const char *);
extern "C" char *strdup(const char *);

extern "C" const char __rcsid_kwif[] =
    "$MirOS: contrib/hosted/tg/code/kwalletcli/kwif3.cc,v 1.3 2009/07/10 10:50:06 tg Exp $";

extern "C" int
kw_io(const char *fld, const char *ent, const char **pwp, const char *vers)
{
	int rv;
	QString localwallet, qfld, qent, qpw;
	KWallet::Wallet *wallet;
	char *env_DISPLAY;

	if (pwp == NULL)
		return (KWE_ABORT);

	/* very basic protection against kdeinit errors */
	if (!(env_DISPLAY = getenv("DISPLAY")) || !*env_DISPLAY)
		return (KWE_NOWALLET);

	qfld = QString::fromUtf8(fld);
	qent = QString::fromUtf8(ent);
	if (*pwp != NULL)
		qpw = QString::fromUtf8(*pwp);

	/* this is ridiculous */
	KAboutData aboutData("kwalletcli", I18N_NOOP("KWallet CLI"), vers);
	KCmdLineArgs::init(&aboutData);
	KApplication app(false, false);

	localwallet = KWallet::Wallet::LocalWallet();
	wallet = KWallet::Wallet::openWallet(localwallet);

	if (!wallet) {
		rv = KWE_NOWALLET;
		goto out;
	}

	if (!wallet->hasFolder(qfld)) {
		if (*pwp == NULL) {
			rv = KWE_NOFOLDER;
			goto out;
		}
		wallet->createFolder(qfld);
	}

	if (!wallet->setFolder(qfld)) {
		rv = KWE_ERRFOLDER;
		goto out;
	}

	if (*pwp == NULL) {
		if (!wallet->hasEntry(qent)) {
			rv = KWE_NOENTRY;
			goto out;
		}
		qpw = "";
		if (wallet->readPassword(qent, qpw)) {
			rv = KWE_ERRENTRY;
			goto out;
		}
		rv = KWE_OK_GET;
		*pwp = strdup((const char *)qpw.utf8());
	} else {
		if (wallet->writePassword(qent, qpw)) {
			rv = KWE_ERR_SET;
			goto out;
		}
		rv = KWE_OK_SET;
	}

 out:
	delete wallet;
	return (rv);
}