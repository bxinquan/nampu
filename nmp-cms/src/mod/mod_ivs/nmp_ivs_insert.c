#include "nmp_debug.h"
#include "nmp_appcore.h"
#include "nmp_mod_ivs.h"

void
nmp_cms_ivs_insert( void )
{
	NmpAppMod *mod;

	mod = g_object_new(NMP_TYPE_MODIVS, NULL);
	if (G_UNLIKELY(!mod))
	{
		jpf_error("<JpfModIvs> alloc mod ivs failed!");
		FATAL_ERROR_EXIT;
	}

	nmp_app_mod_setup((NmpAppMod*)mod);
	jpf_afx_mod_insert(BUSSLOT_POS_IVS, mod);
}


//:~ End
