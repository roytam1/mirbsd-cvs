# $MirOS: src/lib/libssl/crypto/Makefile,v 1.43 2015/10/09 22:20:27 tg Exp $
# $OpenBSD: Makefile,v 1.46 2006/10/14 19:43:57 drahn Exp $

.include <bsd.own.mk>

SHLIB_VERSION?=	16.1
LIB=		crypto
LDFLAGS+=	-Wl,-Bsymbolic

SSLEAYDIST=	src
SSL_SRC=	${.CURDIR}/../${SSLEAYDIST}
LCRYPTO_SRC=	${SSL_SRC}/crypto

CPPFLAGS+=	-I${.CURDIR}/../${SSLEAYDIST} -I${LCRYPTO_SRC}
CPPFLAGS+=	-idirafter ${.OBJDIR}

SRCS+=	o_time.c
SRCS+=	cryptlib.c ex_data.c cpt_err.c mem.c mem_dbg.c
SRCS+=	tmdiff.c cversion.c uid.c
SRCS+=	md2_dgst.c md2_one.c
SRCS+=	hmac.c
SRCS+=	aes_cbc.c aes_cfb.c aes_ctr.c aes_ecb.c aes_ofb.c aes_misc.c
SRCS+=	cbc_cksm.c cbc_enc.c cfb64enc.c cfb_enc.c \
	ecb3_enc.c ecb_enc.c enc_read.c enc_writ.c \
	ofb64enc.c ofb_enc.c pcbc_enc.c \
	qud_cksm.c rand_key.c rpc_enc.c set_key.c \
	des_enc.c des_old2.c fcrypt_b.c \
	fcrypt.c xcbc_enc.c ede_cbcm_enc.c \
	str2key.c cfb64ede.c ofb64ede.c \
	des_old.c read2pwd.c
SRCS+=	rc2_ecb.c rc2_skey.c rc2_cbc.c rc2cfb64.c
SRCS+=	rc2ofb64.c
SRCS+=	bf_cfb64.c bf_ecb.c bf_enc.c bf_ofb64.c bf_skey.c
SRCS+=	c_skey.c c_ecb.c c_cfb64.c c_ofb64.c c_enc.c
SRCS+=	bn_add.c bn_div.c bn_exp.c bn_lib.c
SRCS+=	bn_mul.c bn_print.c bn_rand.c bn_shift.c
SRCS+=	bn_word.c bn_blind.c bn_gcd.c bn_prime.c bn_err.c
SRCS+=	bn_sqr.c bn_recp.c bn_mont.c bn_mpi.c bn_mod.c
SRCS+=	bn_exp2.c bn_ctx.c
SRCS+=	bn_sqrt.c bn_kron.c bn_x931p.c
SRCS+=	rsa_eay.c rsa_gen.c rsa_lib.c rsa_sign.c
SRCS+=	rsa_saos.c rsa_err.c rsa_pk1.c rsa_ssl.c
SRCS+=	rsa_none.c rsa_chk.c rsa_oaep.c rsa_null.c rsa_asn1.c
SRCS+=	rsa_pss.c rsa_x931.c
SRCS+=	dsa_gen.c dsa_key.c dsa_lib.c dsa_vrf.c
SRCS+=	dsa_sign.c dsa_err.c dsa_asn1.c dsa_ossl.c
SRCS+=	dh_gen.c dh_key.c dh_lib.c dh_check.c dh_err.c dh_asn1.c
SRCS+=	buffer.c buf_err.c
SRCS+=	bio_lib.c bio_cb.c bio_err.c bss_mem.c
SRCS+=	bss_null.c bss_fd.c bss_file.c bss_sock.c
SRCS+=	bss_conn.c bf_null.c bf_buff.c
SRCS+=	b_print.c b_dump.c b_sock.c bss_acpt.c
SRCS+=	bf_nbio.c bss_bio.c bss_log.c
SRCS+=	stack.c
SRCS+=	lhash.c lh_stats.c
SRCS+=	randfile.c rand_lib.c rand_egd.c rand_err.c
SRCS+=	mbsdrand.c
SRCS+=	err.c err_all.c err_prn.c
SRCS+=	obj_dat.c obj_lib.c obj_err.c o_names.c
SRCS+=	bio_b64.c e_bf.c p_open.c
SRCS+=	bio_enc.c e_cast.c e_xcbc_d.c m_dss.c m_sha1.c p_seal.c
SRCS+=	bio_md.c e_des.c encode.c m_dss1.c names.c p_sign.c
SRCS+=	bio_ok.c e_des3.c evp_enc.c m_md2.c p_verify.c
SRCS+=	c_all.c evp_err.c evp_acnf.c m_md4.c p5_crpt.c e_old.c
SRCS+=	c_allc.c evp_key.c m_md5.c p5_crpt2.c
SRCS+=	c_alld.c e_null.c evp_lib.c p_dec.c
SRCS+=	digest.c e_rc2.c evp_pbe.c m_null.c p_enc.c
SRCS+=	e_aes.c e_rc4.c evp_pkey.c m_ripemd.c p_lib.c
SRCS+=	pem_sign.c pem_seal.c pem_info.c pem_lib.c pem_pkey.c
SRCS+=	pem_all.c pem_err.c pem_x509.c pem_pk8.c pem_oth.c pem_xaux.c
SRCS+=	ui_err.c ui_lib.c ui_openssl.c ui_compat.c ui_util.c
SRCS+=	a_bitstr.c a_mbstr.c a_utctm.c f_enum.c t_bitst.c x_name.c x_pubkey.c
SRCS+=	a_bool.c a_meth.c a_utf8.c f_int.c t_crl.c tasn_typ.c x_pkey.c
SRCS+=	a_bytes.c a_object.c a_verify.c f_string.c t_pkey.c tasn_utl.c
SRCS+=	a_d2i_fp.c a_octet.c asn1_err.c i2d_pr.c t_req.c x_algor.c x_req.c
SRCS+=	a_digest.c a_print.c asn1_lib.c i2d_pu.c t_spki.c x_attrib.c x_sig.c
SRCS+=	a_dup.c a_set.c asn1_par.c n_pkey.c t_x509.c x_bignum.c x_spki.c
SRCS+=	a_enum.c a_sign.c asn_pack.c nsseq.c t_x509a.c x_val.c
SRCS+=	a_gentm.c a_strex.c d2i_pr.c p5_pbe.c tasn_dec.c x_crl.c x_x509.c
SRCS+=	a_hdr.c a_strnid.c d2i_pu.c p5_pbev2.c tasn_enc.c x_exten.c x_x509a.c
SRCS+=	a_i2d_fp.c a_time.c evp_asn1.c tasn_fre.c x_info.c
SRCS+=	a_int.c a_type.c p8_pkey.c tasn_new.c x_long.c asn_moid.c
SRCS+=	x509_d2.c x509_lu.c x509_set.c x509_vfy.c x509spki.c by_dir.c
SRCS+=	x509_def.c x509_obj.c x509_trs.c x509cset.c x509type.c by_file.c
SRCS+=	x509_att.c x509_err.c x509_r2x.c x509_txt.c x509name.c x_all.c
SRCS+=	x509_cmp.c x509_ext.c x509_req.c x509_v3.c x509rset.c
SRCS+=	v3_akey.c v3_alt.c v3_bcons.c v3_bitst.c v3_conf.c v3_cpols.c
SRCS+=	v3_crld.c v3_enum.c v3_extku.c v3_genn.c v3_hex.c v3_ia5.c v3_int.c
SRCS+=	v3_lib.c v3_pku.c v3_prn.c v3_skey.c v3_sxnet.c v3_utl.c
SRCS+=	v3err.c v3_info.c v3_purp.c v3_ocsp.c v3_akeya.c v3_pci.c v3_pcia.c
SRCS+=	conf_err.c conf_lib.c conf_def.c conf_api.c conf_mod.c conf_mall.c
SRCS+=	conf_sap.c
SRCS+=	txt_db.c
SRCS+=	pk7_lib.c pkcs7err.c
SRCS+=	pk7_asn1.c pk7_doit.c pk7_mime.c
SRCS+=	pk7_attr.c pk7_smime.c
SRCS+=	p12_add.c p12_crpt.c p12_init.c p12_mutl.c p12_p8e.c
SRCS+=	p12_asn.c p12_crt.c p12_key.c p12_npas.c p12_utl.c
SRCS+=	p12_attr.c p12_decr.c p12_kiss.c p12_p8d.c pk12err.c
SRCS+=	eng_all.c eng_openssl.c eng_ctrl.c eng_pkey.c
SRCS+=	eng_dyn.c eng_table.c tb_cipher.c eng_err.c
SRCS+=	hw_cryptodev.c eng_cnf.c
SRCS+=	tb_dh.c eng_fat.c tb_digest.c eng_init.c
SRCS+=	tb_dsa.c eng_lib.c tb_rand.c eng_list.c
SRCS+=	tb_rsa.c
SRCS+=	dso_dl.c dso_dlfcn.c dso_err.c dso_lib.c dso_null.c
SRCS+=	dso_openssl.c dso_win32.c dso_vms.c
SRCS+=	ocsp_asn.c ocsp_err.c ocsp_ht.c ocsp_prn.c ocsp_vfy.c
SRCS+=	ocsp_cl.c ocsp_ext.c ocsp_lib.c ocsp_srv.c

.PATH:	${LCRYPTO_SRC}/md2 \
	${LCRYPTO_SRC}/hmac ${LCRYPTO_SRC}/bf \
	${LCRYPTO_SRC}/des ${LCRYPTO_SRC}/rc2 \
	${LCRYPTO_SRC}/cast ${LCRYPTO_SRC}/bn ${LCRYPTO_SRC}/rsa \
	${LCRYPTO_SRC}/dsa ${LCRYPTO_SRC}/dh ${LCRYPTO_SRC}/buffer \
	${LCRYPTO_SRC}/bio ${LCRYPTO_SRC}/stack ${LCRYPTO_SRC}/lhash \
	${LCRYPTO_SRC}/rand ${LCRYPTO_SRC}/err ${LCRYPTO_SRC}/objects \
	${LCRYPTO_SRC}/evp ${LCRYPTO_SRC}/pem ${LCRYPTO_SRC}/asn1 \
	${LCRYPTO_SRC}/asn1 ${LCRYPTO_SRC}/x509 ${LCRYPTO_SRC}/conf \
	${LCRYPTO_SRC}/pkcs7 ${LCRYPTO_SRC}/x509v3 ${LCRYPTO_SRC}/pkcs12 \
	${LCRYPTO_SRC}/txt_db \
	${LCRYPTO_SRC}/engine ${LCRYPTO_SRC}/dso ${LCRYPTO_SRC}/ui \
	${LCRYPTO_SRC}/ocsp ${LCRYPTO_SRC}/aes \
	${LCRYPTO_SRC} ${.CURDIR}/arch/${MACHINE_ARCH} \
	${LCRYPTO_SRC}/bn/asm

HDRS=\
	crypto/aes/aes.h \
	crypto/asn1/asn1.h \
	crypto/asn1/asn1_mac.h \
	crypto/asn1/asn1t.h \
	crypto/bf/blowfish.h \
	crypto/bio/bio.h \
	crypto/bn/bn.h \
	crypto/buffer/buffer.h \
	crypto/cast/cast.h \
	crypto/conf/conf.h \
	crypto/conf/conf_api.h \
	crypto/crypto.h \
	crypto/des/des.h \
	crypto/des/des_old.h \
	crypto/dh/dh.h \
	crypto/dsa/dsa.h \
	crypto/dso/dso.h \
	crypto/ebcdic.h \
	crypto/engine/engine.h \
	crypto/err/err.h \
	crypto/evp/evp.h \
	crypto/hmac/hmac.h \
	crypto/lhash/lhash.h \
	crypto/md2/md2.h \
	${.CURDIR}/md4.h \
	${.OBJDIR}/md5.h \
	crypto/objects/objects.h \
	crypto/ocsp/ocsp.h \
	crypto/opensslv.h \
	crypto/ossl_typ.h \
	crypto/pem/pem.h \
	crypto/pem/pem2.h \
	crypto/pkcs12/pkcs12.h \
	crypto/pkcs7/pkcs7.h \
	crypto/rand/rand.h \
	crypto/rc2/rc2.h \
	${.CURDIR}/rc4.h \
	${.CURDIR}/ripemd.h \
	crypto/rsa/rsa.h \
	${.CURDIR}/sha.h \
	crypto/stack/safestack.h \
	crypto/stack/stack.h \
	crypto/symhacks.h \
	crypto/tmdiff.h \
	crypto/txt_db/txt_db.h \
	crypto/ui/ui.h \
	crypto/ui/ui_compat.h \
	crypto/x509/x509.h \
	crypto/x509/x509_vfy.h \
	crypto/x509v3/x509v3.h \
	e_os2.h \
	${.CURDIR}/fips.h \
	${.CURDIR}/fips_rand.h \
	${.CURDIR}/arch/${MACHINE_ARCH}/opensslconf.h \
	${.OBJDIR}/obj_mac.h
HDRSRC=	${SSL_SRC}
HDRDST=	${DESTDIR}/usr/include/openssl

prereq: obj_mac.h

GENERATED+=	md5.h
CLEANFILES+=	mbsd_md5.c

prereq: md5.h

md5.h: md4.h
	sed -e 's/md4/md5/g' -e 's/MD4/MD5/g' <$> >$@

mbsd_md5.c: mbsd_md4.c
	sed -e 's/md4/md5/g' -e 's/MD4/MD5/g' <$> >$@

.for _i in md4 md5 rmd160 sha1
CLEANFILES+=	mbsd_${_i}_one.c
SRCS+=		mbsd_${_i}_one.c

mbsd_${_i}_one.c: mbsd_${_i}.c
	-unifdef -DL_one $> >$@
.endfor

GENERATED+=	obj_mac.h obj_dat.h
CLEANFILES+=	${GENERATED} obj_mac.num.tmp
SSL_OBJECTS=	${SSL_SRC}/crypto/objects

obj_mac.h: ${SSL_OBJECTS}/objects.h ${SSL_OBJECTS}/obj_mac.num ${SSL_OBJECTS}/objects.txt
	cat ${SSL_OBJECTS}/obj_mac.num >obj_mac.num.tmp
	/usr/bin/perl ${SSL_OBJECTS}/objects.pl ${SSL_OBJECTS}/objects.txt obj_mac.num.tmp obj_mac.h

obj_dat.h: obj_mac.h
	/usr/bin/perl ${SSL_OBJECTS}/obj_dat.pl obj_mac.h obj_dat.h

.if (${MACHINE_ARCH} == "i386")
CPPFLAGS+= -DAES_ASM
CPPFLAGS+= -DOPENBSD_DES_ASM
SSLASM=\
	aes aes-586 \
	bn bn-586 \
	bn co-586 \
	des des-586
.  for dir f in ${SSLASM}
SRCS+=	${f}.S
GENERATED+=${f}.S
${f}.S: ${LCRYPTO_SRC}/${dir}/asm/${f}.pl ${LCRYPTO_SRC}/perlasm/x86unix.pl
	/usr/bin/perl -I${LCRYPTO_SRC}/perlasm -I${LCRYPTO_SRC}/${dir}/asm \
		${LCRYPTO_SRC}/${dir}/asm/${f}.pl openbsd-elf 486 >$@
.  endfor
.else
SRCS+= aes_core.c
SRCS+= bn_asm.c
.endif

SRCS+=	mbsd_memclr.c
SRCS+=	mbsd_rc4.c

SRCS+=	mbsd_md4.c
SRCS+=	mbsd_md5.c
SRCS+=	mbsd_rmd160.c
SRCS+=	mbsd_sha1.c

all beforedepend: ${GENERATED}

.include <bsd.lib.mk>
