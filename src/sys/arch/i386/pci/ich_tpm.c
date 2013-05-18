/* $MirOS: src/share/misc/licence.template,v 1.28 2008/11/14 15:33:44 tg Rel $ */

/*-
 * Copyright (c) 2009
 *	Thorsten Glaser <tg@mirbsd.org>
 *
 * Provided that these terms and disclaimer and all copyright notices
 * are retained or reproduced in an accompanying document, permission
 * is granted to deal in this work without restriction, including un-
 * limited rights to use, publicly perform, distribute, sell, modify,
 * merge, give away, or sublicence.
 *
 * This work is provided "AS IS" and WITHOUT WARRANTY of any kind, to
 * the utmost extent permitted by applicable law, neither express nor
 * implied; without malicious intent or gross negligence. In no event
 * may a licensor, author or contributor be held liable for indirect,
 * direct, other damage, loss, or other issues arising in any way out
 * of dealing in the work, even if advised of the possibility of such
 * damage or existence of a defect, except proven that it results out
 * of said person's immediate fault when using the work as intended.
 */

#include <sys/param.h>
#include <sys/device.h>
#include <sys/systm.h>
#include <sys/timeout.h>
#include <machine/bus.h>
#include <dev/ic/tpm.h>
#include <dev/pci/pcidevs.h>
#include <dev/pci/pcireg.h>
#include <dev/pci/pcivar.h>

/* PCI configuration addresses */
#define PCI_GEN1_DEC			0xE4
#define PCI_LPC_EN			0xE6
#define PCI_GEN2_DEC			0xEC

/* TPM Base */
#define TPM_ATMEL_BASE			0x400

extern struct cfdriver tpm_cd;

void ichpcib_attach_tpm(struct device *, struct device *,
    struct pci_attach_args *);

struct cfattach ich_tpm_ca = {
	sizeof (struct tpm_softc), tpm_match, tpm_attach
};


void ichpcib_attach_tpm(struct device *parent, struct device *self,
    struct pci_attach_args *pa)
{
	enum tpm_chip_type chiptype = TPM_INVALID_CHIP;
	int lpcenable, tpminfo;
	struct tpm_attach_args ta;
	struct cfdata cf;

	if (PCI_VENDOR(pa->pa_id) == PCI_VENDOR_INTEL) {
		switch (PCI_PRODUCT(pa->pa_id)) {
		case PCI_PRODUCT_INTEL_82801BA_LPC:
			chiptype = ICH2LPC;
			break;
		case PCI_PRODUCT_INTEL_82801CAM_LPC:
			chiptype = ICH3LPCM;
			break;
		case PCI_PRODUCT_INTEL_82801DB_LPC:
			chiptype = ICH4LPC;
			break;
		case PCI_PRODUCT_INTEL_82801DBM_LPC:
			chiptype = ICH4LPCM;
			break;
		}
	}

	if (chiptype == TPM_INVALID_CHIP)
		return;

	/* Enable the LPC */
	lpcenable = pci_conf_read(pa->pa_pc, pa->pa_tag, PCI_GEN1_DEC);
	lpcenable |= 0x20000000;
	pci_conf_write(pa->pa_pc, pa->pa_tag, PCI_GEN1_DEC, lpcenable);
	/* Verify it was turned on */
	if ((chiptype == ICH3LPCM) || (chiptype == ICH4LPCM)) {
		lpcenable = pci_conf_read(pa->pa_pc, pa->pa_tag, PCI_GEN1_DEC);
		if ((lpcenable & 0x20000000) == 0) {
			printf("tpm: cannot enable LPC\n");
			return;
		}
	}

	/* Initialise TPM */
	tpminfo = pci_conf_read(pa->pa_pc, pa->pa_tag, PCI_GEN2_DEC);
	tpminfo = (tpminfo & 0xffff0000) | (TPM_ATMEL_BASE & 0xfff0);
	/* if ((chiptype == ICH3LPCM) || (chiptype == ICH4LPCM)) */
		tpminfo |= 0x00000001;
	pci_conf_write(pa->pa_pc, pa->pa_tag, PCI_GEN2_DEC, tpminfo);


	bzero(&ta, sizeof (ta));
	ta.base = TPM_ATMEL_BASE;
	ta.chiptype = chiptype;

	bzero(&cf, sizeof (cf));
	cf.cf_attach = &ich_tpm_ca;
	cf.cf_driver = &tpm_cd;
	config_attach(NULL, &cf, &ta, NULL);
}
