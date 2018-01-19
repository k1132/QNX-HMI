/**
* \file
* Rule describing a data binding in form of read rule and write rule.
* 
* Copyright 2008-2013 by Rightware. All rights reserved.
*/
#ifndef KZU_BINDING_RULE_DIAGNOSTICS_H
#define KZU_BINDING_RULE_DIAGNOSTICS_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzuBindingRule;


/**
 * Returns the string containing information about the binding.
 * \param[out] out_string string containing information about the binding. The caller should delete it.
 */
kzsError kzuBindingRuleGetDetails(const struct KzuBindingRule* bindingRule, kzMutableString* out_detailsString);


KZ_HEADER_END


#endif
