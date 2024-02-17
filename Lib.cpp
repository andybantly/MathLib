#include "Lib.h"
#pragma warning(disable:6385)

using namespace std;

const string ones[] = { "Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten",
							   "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen","Sixteen", "Seventeen", "Eighteen", "Nineteen" };
const string tens[] = { "", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety", "Hundred" };

const string huns[] =
{
	"Thousand", "Million", "Billion", "Trillion", "Quadrillion", "Quintillion", "Sextillion", "Septillion",
	"Octillion", "Nonillion", "Decillion", "Undecillion", "Duodecillion", "Tredecillion", "Quattuordecillion", "Quindecillion",
	"Sexdecillion", "Septendecillion", "Octodecillion", "Novemdecillion", "Vigintillion", "Unvigintillion", "Duovigintillion",
	"Tresvigintillion", "Quattuorvigintillion", "Quinvigintillion", "Sesvigintillion", "Septemvigintillion", "Octovigintillion",
	"Novemvigintillion", "Trigintillion", "untrigintillion", "duotrigintillion", "tretrigintillion", "quattuortrigintillion",
	"quintrigintillion", "sextrigintillion", "septentrigintillion", "octatrigintillion", "novemtrigintillion", "quadragintillion", "unquadragintillion", "duoquadragintillion", "trequadragintillion", "quattuorquadragintillion",
	"quinquadragintillion", "sexquadragintillion", "septenquadragintillion", "octaquadragintillion", "novemquadragintillion", "quinquagintillion", "unquinquagintillion",
	"duoquinquagintillion", "trequinquagintillion", "quattuorquinquagintillion", "quinquinquagintillion", "sexquinquagintillion", "septenquinquagintillion", "octaquinquagintillion",
	"novemquinquagintillion", "sexagintillion", "unsexagintillion", "duosexagintillion", "tresexagintillion", "quattuorsexagintillion", "quinsexagintillion",
	"sexsexagintillion", "septensexagintillion", "octasexagintillion", "novemsexagintillion", "septuagintillion", "unseptuagintillion", "duoseptuagintillion",
	"treseptuagintillion", "quattuorseptuagintillion", "quinseptuagintillion", "sexseptuagintillion", "septenseptuagintillion", "octaseptuagintillion", "novemseptuagintillion",
	"octagintillion", "unoctogintillion", "duooctogintillion", "treoctogintillion", "quattuoroctogintillion", "quinoctogintillion", "sexoctogintillion",
	"septenoctogintillion", "octaoctogintillion", "novemoctogintillion", "nonagintillion", "unnonagintillion", "duononagintillion", "trenonagintillion",
	"quattuornonagintillion", "quinnonagintillion", "sexnonagintillion", "septennonagintillion", "octanonagintillion", "novemnonagintillion", "centillion",
	"cenuntillion", "cendotillion", "centretillion", "cenquattuortillion", "cenquintillion", "censextillion", "censeptentillion",
	"cenoctotillion", "cennovemtillion", "cendecillion", "cenundecillion", "cendodecillion", "centredecillion", "cenquattuordecillion",
	"cenquindecillion", "censexdecillion", "censeptendecillion", "cenoctodecillion", "cennovemdecillion", "cenvigintillion", "cenunvigintillion",
	"cendovigintillion", "centrevigintillion", "cenquattuorvigintillion", "cenquinvigintillion", "censexvigintillion", "censeptenvigintillion", "cenoctovigintillion",
	"cennovemvigintillion", "centrigintillion", "cenuntrigintillion", "cendotrigintillion", "centretrigintillion", "cenquattuortrigintillion", "cenquintrigintillion",
	"censextrigintillion", "censeptentrigintillion", "cenoctotrigintillion", "cennovemtrigintillion", "cenquadragintillion", "cenunquadragintillion", "cendoquadragintillion",
	"centrequadragintillion", "cenquattuorquadragintillion", "cenquinquadragintillion", "censexquadragintillion", "censeptenquadragintillion", "cenoctoquadragintillion", "cennovemquadragintillion",
	"cenquinquagintillion", "cenunquinquagintillion", "cendoquinquagintillion", "centrequinquagintillion", "cenquattuorquinquagintillion", "cenquinquinquagintillion", "censexquinquagintillion",
	"censeptenquinquagintillion", "cenoctoquinquagintillion", "cennovemquinquagintillion", "censexagintillion", "cenunsexagintillion", "cendosexagintillion", "centresexagintillion",
	"cenquattuorsexagintillion", "cenquinsexagintillion", "censexsexagintillion", "censeptensexagintillion", "cenoctosexagintillion", "cennovemsexagintillion", "censeptuagintillion",
	"cenunseptuagintillion", "cendoseptuagintillion", "centreseptuagintillion", "cenquattuorseptuagintillion", "cenquinseptuagintillion", "censexseptuagintillion", "censeptenseptuagintillion",
	"cenoctoseptuagintillion", "cennovemseptuagintillion", "cenoctogintillion", "cenunoctogintillion", "cendooctogintillion", "centreoctogintillion", "cenquattuoroctogintillion",
	"cenquinoctogintillion", "censexoctogintillion", "censeptenoctogintillion", "cenoctooctogintillion", "cennovemoctogintillion", "cennonagintillion", "cenunnonagintillion",
	"cendononagintillion", "centrenonagintillion", "cenquattuornonagintillion", "cenquinnonagintillion", "censexnonagintillion", "censeptennonagintillion", "cenoctononagintillion",
	"cennovemnonagintillion", "duocentillion", "duocenuntillion", "duocendotillion", "duocentretillion", "duocenquattuortillion", "duocenquintillion",
	"duocensextillion", "duocenseptentillion", "duocenoctotillion", "duocennovemtillion", "duocendecillion", "duocenundecillion", "duocendodecillion",
	"duocentredecillion", "duocenquattuordecillion", "duocenquindecillion", "duocensexdecillion", "duocenseptendecillion", "duocenoctodecillion", "duocennovemdecillion",
	"duocenvigintillion", "duocenunvigintillion", "duocendovigintillion", "duocentrevigintillion", "duocenquattuorvigintillion", "duocenquinvigintillion", "duocensexvigintillion",
	"duocenseptenvigintillion", "duocenoctovigintillion", "duocennovemvigintillion", "duocentrigintillion", "duocenuntrigintillion", "duocendotrigintillion", "duocentretrigintillion",
	"duocenquattuortrigintillion", "duocenquintrigintillion", "duocensextrigintillion", "duocenseptentrigintillion", "duocenoctotrigintillion", "duocennovemtrigintillion", "duocenquadragintillion",
	"duocenunquadragintillion", "duocendoquadragintillion", "duocentrequadragintillion", "duocenquattuorquadragintillion", "duocenquinquadragintillion", "duocensexquadragintillion", "duocenseptenquadragintillion",
	"duocenoctoquadragintillion", "duocennovemquadragintillion", "duocenquinquagintillion", "duocenunquinquagintillion", "duocendoquinquagintillion", "duocentrequinquagintillion", "duocenquattuorquinquagintillion",
	"duocenquinquinquagintillion", "duocensexquinquagintillion", "duocenseptenquinquagintillion", "duocenoctoquinquagintillion", "duocennovemquinquagintillion", "duocensexagintillion", "duocenunsexagintillion",
	"duocendosexagintillion", "duocentresexagintillion", "duocenquattuorsexagintillion", "duocenquinsexagintillion", "duocensexsexagintillion", "duocenseptensexagintillion", "duocenoctosexagintillion",
	"duocennovemsexagintillion", "duocenseptuagintillion", "duocenunseptuagintillion", "duocendoseptuagintillion", "duocentreseptuagintillion", "duocenquattuorseptuagintillion", "duocenquinseptuagintillion",
	"duocensexseptuagintillion", "duocenseptenseptuagintillion", "duocenoctoseptuagintillion", "duocennovemseptuagintillion", "duocenoctogintillion", "duocenunoctogintillion", "duocendooctogintillion",
	"duocentreoctogintillion", "duocenquattuoroctogintillion", "duocenquinoctogintillion", "duocensexoctogintillion", "duocenseptenoctogintillion", "duocenoctooctogintillion", "duocennovemoctogintillion",
	"duocennonagintillion", "duocenunnonagintillion", "duocendononagintillion", "duocentrenonagintillion", "duocenquattuornonagintillion", "duocenquinnonagintillion", "duocensexnonagintillion",
	"duocenseptennonagintillion", "duocenoctononagintillion", "duocennovemnonagintillion", "trecentillion", "trecenuntillion", "trecendotillion", "trecentretillion",
	"trecenquattuortillion", "trecenquintillion", "trecensextillion", "trecenseptentillion", "trecenoctotillion", "trecennovemtillion", "trecendecillion",
	"trecenundecillion", "trecendodecillion", "trecentredecillion", "trecenquattuordecillion", "trecenquindecillion", "trecensexdecillion", "trecenseptendecillion",
	"trecenoctodecillion", "trecennovemdecillion", "trecenvigintillion", "trecenunvigintillion", "trecendovigintillion", "trecentrevigintillion", "trecenquattuorvigintillion",
	"trecenquinvigintillion", "trecensexvigintillion", "trecenseptenvigintillion", "trecenoctovigintillion", "trecennovemvigintillion", "trecentrigintillion", "trecenuntrigintillion",
	"trecendotrigintillion", "trecentretrigintillion", "trecenquattuortrigintillion", "trecenquintrigintillion", "trecensextrigintillion", "trecenseptentrigintillion", "trecenoctotrigintillion",
	"trecennovemtrigintillion", "trecenquadragintillion", "trecenunquadragintillion", "trecendoquadragintillion", "trecentrequadragintillion", "trecenquattuorquadragintillion", "trecenquinquadragintillion",
	"trecensexquadragintillion", "trecenseptenquadragintillion", "trecenoctoquadragintillion", "trecennovemquadragintillion", "trecenquinquagintillion", "trecenunquinquagintillion", "trecendoquinquagintillion",
	"trecentrequinquagintillion", "trecenquattuorquinquagintillion", "trecenquinquinquagintillion", "trecensexquinquagintillion", "trecenseptenquinquagintillion", "trecenoctoquinquagintillion", "trecennovemquinquagintillion",
	"trecensexagintillion", "trecenunsexagintillion", "trecendosexagintillion", "trecentresexagintillion", "trecenquattuorsexagintillion", "trecenquinsexagintillion", "trecensexsexagintillion",
	"trecenseptensexagintillion", "trecenoctosexagintillion", "trecennovemsexagintillion", "trecenseptuagintillion", "trecenunseptuagintillion", "trecendoseptuagintillion", "trecentreseptuagintillion",
	"trecenquattuorseptuagintillion", "trecenquinseptuagintillion", "trecensexseptuagintillion", "trecenseptenseptuagintillion", "trecenoctoseptuagintillion", "trecennovemseptuagintillion", "trecenoctogintillion",
	"trecenunoctogintillion", "trecendooctogintillion", "trecentreoctogintillion", "trecenquattuoroctogintillion", "trecenquinoctogintillion", "trecensexoctogintillion", "trecenseptenoctogintillion",
	"trecenoctooctogintillion", "trecennovemoctogintillion", "trecennonagintillion", "trecenunnonagintillion", "trecendononagintillion", "trecentrenonagintillion", "trecenquattuornonagintillion",
	"trecenquinnonagintillion", "trecensexnonagintillion", "trecenseptennonagintillion", "trecenoctononagintillion", "trecennovemnonagintillion", "quadringentillion", "quadringenuntillion",
	"quadringendotillion", "quadringentretillion", "quadringenquattuortillion", "quadringenquintillion", "quadringensextillion", "quadringenseptentillion", "quadringenoctotillion",
	"quadringennovemtillion", "quadringendecillion", "quadringenundecillion", "quadringendodecillion", "quadringentredecillion", "quadringenquattuordecillion", "quadringenquindecillion",
	"quadringensexdecillion", "quadringenseptendecillion", "quadringenoctodecillion", "quadringennovemdecillion", "quadringenvigintillion", "quadringenunvigintillion", "quadringendovigintillion",
	"quadringentrevigintillion", "quadringenquattuorvigintillion", "quadringenquinvigintillion", "quadringensexvigintillion", "quadringenseptenvigintillion", "quadringenoctovigintillion", "quadringennovemvigintillion",
	"quadringentrigintillion", "quadringenuntrigintillion", "quadringendotrigintillion", "quadringentretrigintillion", "quadringenquattuortrigintillion", "quadringenquintrigintillion", "quadringensextrigintillion",
	"quadringenseptentrigintillion", "quadringenoctotrigintillion", "quadringennovemtrigintillion", "quadringenquadragintillion", "quadringenunquadragintillion", "quadringendoquadragintillion", "quadringentrequadragintillion",
	"quadringenquattuorquadragintillion", "quadringenquinquadragintillion", "quadringensexquadragintillion", "quadringenseptenquadragintillion", "quadringenoctoquadragintillion", "quadringennovemquadragintillion", "quadringenquinquagintillion",
	"quadringenunquinquagintillion", "quadringendoquinquagintillion", "quadringentrequinquagintillion", "quadringenquattuorquinquagintillion", "quadringenquinquinquagintillion", "quadringensexquinquagintillion", "quadringenseptenquinquagintillion",
	"quadringenoctoquinquagintillion", "quadringennovemquinquagintillion", "quadringensexagintillion", "quadringenunsexagintillion", "quadringendosexagintillion", "quadringentresexagintillion", "quadringenquattuorsexagintillion",
	"quadringenquinsexagintillion", "quadringensexsexagintillion", "quadringenseptensexagintillion", "quadringenoctosexagintillion", "quadringennovemsexagintillion", "quadringenseptuagintillion", "quadringenunseptuagintillion",
	"quadringendoseptuagintillion", "quadringentreseptuagintillion", "quadringenquattuorseptuagintillion", "quadringenquinseptuagintillion", "quadringensexseptuagintillion", "quadringenseptenseptuagintillion", "quadringenoctoseptuagintillion",
	"quadringennovemseptuagintillion", "quadringenoctogintillion", "quadringenunoctogintillion", "quadringendooctogintillion", "quadringentreoctogintillion", "quadringenquattuoroctogintillion", "quadringenquinoctogintillion",
	"quadringensexoctogintillion", "quadringenseptenoctogintillion", "quadringenoctooctogintillion", "quadringennovemoctogintillion", "quadringennonagintillion", "quadringenunnonagintillion", "quadringendononagintillion",
	"quadringentrenonagintillion", "quadringenquattuornonagintillion", "quadringenquinnonagintillion", "quadringensexnonagintillion", "quadringenseptennonagintillion", "quadringenoctononagintillion", "quadringennovemnonagintillion",
	"quingentillion", "quingenuntillion", "quingendotillion", "quingentretillion", "quingenquattuortillion", "quingenquintillion", "quingensextillion",
	"quingenseptentillion", "quingenoctotillion", "quingennovemtillion", "quingendecillion", "quingenundecillion", "quingendodecillion", "quingentredecillion",
	"quingenquattuordecillion", "quingenquindecillion", "quingensexdecillion", "quingenseptendecillion", "quingenoctodecillion", "quingennovemdecillion", "quingenvigintillion",
	"quingenunvigintillion", "quingendovigintillion", "quingentrevigintillion", "quingenquattuorvigintillion", "quingenquinvigintillion", "quingensexvigintillion", "quingenseptenvigintillion",
	"quingenoctovigintillion", "quingennovemvigintillion", "quingentrigintillion", "quingenuntrigintillion", "quingendotrigintillion", "quingentretrigintillion", "quingenquattuortrigintillion",
	"quingenquintrigintillion", "quingensextrigintillion", "quingenseptentrigintillion", "quingenoctotrigintillion", "quingennovemtrigintillion", "quingenquadragintillion", "quingenunquadragintillion",
	"quingendoquadragintillion", "quingentrequadragintillion", "quingenquattuorquadragintillion", "quingenquinquadragintillion", "quingensexquadragintillion", "quingenseptenquadragintillion", "quingenoctoquadragintillion",
	"quingennovemquadragintillion", "quingenquinquagintillion", "quingenunquinquagintillion", "quingendoquinquagintillion", "quingentrequinquagintillion", "quingenquattuorquinquagintillion", "quingenquinquinquagintillion",
	"quingensexquinquagintillion", "quingenseptenquinquagintillion", "quingenoctoquinquagintillion", "quingennovemquinquagintillion", "quingensexagintillion", "quingenunsexagintillion", "quingendosexagintillion",
	"quingentresexagintillion", "quingenquattuorsexagintillion", "quingenquinsexagintillion", "quingensexsexagintillion", "quingenseptensexagintillion", "quingenoctosexagintillion", "quingennovemsexagintillion",
	"quingenseptuagintillion", "quingenunseptuagintillion", "quingendoseptuagintillion", "quingentreseptuagintillion", "quingenquattuorseptuagintillion", "quingenquinseptuagintillion", "quingensexseptuagintillion",
	"quingenseptenseptuagintillion", "quingenoctoseptuagintillion", "quingennovemseptuagintillion", "quingenoctogintillion", "quingenunoctogintillion", "quingendooctogintillion", "quingentreoctogintillion",
	"quingenquattuoroctogintillion", "quingenquinoctogintillion", "quingensexoctogintillion", "quingenseptenoctogintillion", "quingenoctooctogintillion", "quingennovemoctogintillion", "quingennonagintillion",
	"quingenunnonagintillion", "quingendononagintillion", "quingentrenonagintillion", "quingenquattuornonagintillion", "quingenquinnonagintillion", "quingensexnonagintillion", "quingenseptennonagintillion",
	"quingenoctononagintillion", "quingennovemnonagintillion", "sescentillion", "sescenuntillion", "sescendotillion", "sescentretillion", "sescenquattuortillion",
	"sescenquintillion", "sescensextillion", "sescenseptentillion", "sescenoctotillion", "sescennovemtillion", "sescendecillion", "sescenundecillion",
	"sescendodecillion", "sescentredecillion", "sescenquattuordecillion", "sescenquindecillion", "sescensexdecillion", "sescenseptendecillion", "sescenoctodecillion",
	"sescennovemdecillion", "sescenvigintillion", "sescenunvigintillion", "sescendovigintillion", "sescentrevigintillion", "sescenquattuorvigintillion", "sescenquinvigintillion",
	"sescensexvigintillion", "sescenseptenvigintillion", "sescenoctovigintillion", "sescennovemvigintillion", "sescentrigintillion", "sescenuntrigintillion", "sescendotrigintillion",
	"sescentretrigintillion", "sescenquattuortrigintillion", "sescenquintrigintillion", "sescensextrigintillion", "sescenseptentrigintillion", "sescenoctotrigintillion", "sescennovemtrigintillion",
	"sescenquadragintillion", "sescenunquadragintillion", "sescendoquadragintillion", "sescentrequadragintillion", "sescenquattuorquadragintillion", "sescenquinquadragintillion", "sescensexquadragintillion",
	"sescenseptenquadragintillion", "sescenoctoquadragintillion", "sescennovemquadragintillion", "sescenquinquagintillion", "sescenunquinquagintillion", "sescendoquinquagintillion", "sescentrequinquagintillion",
	"sescenquattuorquinquagintillion", "sescenquinquinquagintillion", "sescensexquinquagintillion", "sescenseptenquinquagintillion", "sescenoctoquinquagintillion", "sescennovemquinquagintillion", "sescensexagintillion",
	"sescenunsexagintillion", "sescendosexagintillion", "sescentresexagintillion", "sescenquattuorsexagintillion", "sescenquinsexagintillion", "sescensexsexagintillion", "sescenseptensexagintillion",
	"sescenoctosexagintillion", "sescennovemsexagintillion", "sescenseptuagintillion", "sescenunseptuagintillion", "sescendoseptuagintillion", "sescentreseptuagintillion", "sescenquattuorseptuagintillion",
	"sescenquinseptuagintillion", "sescensexseptuagintillion", "sescenseptenseptuagintillion", "sescenoctoseptuagintillion", "sescennovemseptuagintillion", "sescenoctogintillion", "sescenunoctogintillion",
	"sescendooctogintillion", "sescentreoctogintillion", "sescenquattuoroctogintillion", "sescenquinoctogintillion", "sescensexoctogintillion", "sescenseptenoctogintillion", "sescenoctooctogintillion",
	"sescennovemoctogintillion", "sescennonagintillion", "sescenunnonagintillion", "sescendononagintillion", "sescentrenonagintillion", "sescenquattuornonagintillion", "sescenquinnonagintillion",
	"sescensexnonagintillion", "sescenseptennonagintillion", "sescenoctononagintillion", "sescennovemnonagintillion", "septingentillion", "septingenuntillion", "septingendotillion",
	"septingentretillion", "septingenquattuortillion", "septingenquintillion", "septingensextillion", "septingenseptentillion", "septingenoctotillion", "septingennovemtillion",
	"septingendecillion", "septingenundecillion", "septingendodecillion", "septingentredecillion", "septingenquattuordecillion", "septingenquindecillion", "septingensexdecillion",
	"septingenseptendecillion", "septingenoctodecillion", "septingennovemdecillion", "septingenvigintillion", "septingenunvigintillion", "septingendovigintillion", "septingentrevigintillion",
	"septingenquattuorvigintillion", "septingenquinvigintillion", "septingensexvigintillion", "septingenseptenvigintillion", "septingenoctovigintillion", "septingennovemvigintillion", "septingentrigintillion",
	"septingenuntrigintillion", "septingendotrigintillion", "septingentretrigintillion", "septingenquattuortrigintillion", "septingenquintrigintillion", "septingensextrigintillion", "septingenseptentrigintillion",
	"septingenoctotrigintillion", "septingennovemtrigintillion", "septingenquadragintillion", "septingenunquadragintillion", "septingendoquadragintillion", "septingentrequadragintillion", "septingenquattuorquadragintillion",
	"septingenquinquadragintillion", "septingensexquadragintillion", "septingenseptenquadragintillion", "septingenoctoquadragintillion", "septingennovemquadragintillion", "septingenquinquagintillion", "septingenunquinquagintillion",
	"septingendoquinquagintillion", "septingentrequinquagintillion", "septingenquattuorquinquagintillion", "septingenquinquinquagintillion", "septingensexquinquagintillion", "septingenseptenquinquagintillion", "septingenoctoquinquagintillion",
	"septingennovemquinquagintillion", "septingensexagintillion", "septingenunsexagintillion", "septingendosexagintillion", "septingentresexagintillion", "septingenquattuorsexagintillion", "septingenquinsexagintillion",
	"septingensexsexagintillion", "septingenseptensexagintillion", "septingenoctosexagintillion", "septingennovemsexagintillion", "septingenseptuagintillion", "septingenunseptuagintillion", "septingendoseptuagintillion",
	"septingentreseptuagintillion", "septingenquattuorseptuagintillion", "septingenquinseptuagintillion", "septingensexseptuagintillion", "septingenseptenseptuagintillion", "septingenoctoseptuagintillion", "septingennovemseptuagintillion",
	"septingenoctogintillion", "septingenunoctogintillion", "septingendooctogintillion", "septingentreoctogintillion", "septingenquattuoroctogintillion", "septingenquinoctogintillion", "septingensexoctogintillion",
	"septingenseptenoctogintillion", "septingenoctooctogintillion", "septingennovemoctogintillion", "septingennonagintillion", "septingenunnonagintillion", "septingendononagintillion", "septingentrenonagintillion",
	"septingenquattuornonagintillion", "septingenquinnonagintillion", "septingensexnonagintillion", "septingenseptennonagintillion", "septingenoctononagintillion", "septingennovemnonagintillion", "octingentillion",
	"octingenuntillion", "octingendotillion", "octingentretillion", "octingenquattuortillion", "octingenquintillion", "octingensextillion", "octingenseptentillion",
	"octingenoctotillion", "octingennovemtillion", "octingendecillion", "octingenundecillion", "octingendodecillion", "octingentredecillion", "octingenquattuordecillion",
	"octingenquindecillion", "octingensexdecillion", "octingenseptendecillion", "octingenoctodecillion", "octingennovemdecillion", "octingenvigintillion", "octingenunvigintillion",
	"octingendovigintillion", "octingentrevigintillion", "octingenquattuorvigintillion", "octingenquinvigintillion", "octingensexvigintillion", "octingenseptenvigintillion", "octingenoctovigintillion",
	"octingennovemvigintillion", "octingentrigintillion", "octingenuntrigintillion", "octingendotrigintillion", "octingentretrigintillion", "octingenquattuortrigintillion", "octingenquintrigintillion",
	"octingensextrigintillion", "octingenseptentrigintillion", "octingenoctotrigintillion", "octingennovemtrigintillion", "octingenquadragintillion", "octingenunquadragintillion", "octingendoquadragintillion",
	"octingentrequadragintillion", "octingenquattuorquadragintillion", "octingenquinquadragintillion", "octingensexquadragintillion", "octingenseptenquadragintillion", "octingenoctoquadragintillion", "octingennovemquadragintillion",
	"octingenquinquagintillion", "octingenunquinquagintillion", "octingendoquinquagintillion", "octingentrequinquagintillion", "octingenquattuorquinquagintillion", "octingenquinquinquagintillion", "octingensexquinquagintillion",
	"octingenseptenquinquagintillion", "octingenoctoquinquagintillion", "octingennovemquinquagintillion", "octingensexagintillion", "octingenunsexagintillion", "octingendosexagintillion", "octingentresexagintillion",
	"octingenquattuorsexagintillion", "octingenquinsexagintillion", "octingensexsexagintillion", "octingenseptensexagintillion", "octingenoctosexagintillion", "octingennovemsexagintillion", "octingenseptuagintillion",
	"octingenunseptuagintillion", "octingendoseptuagintillion", "octingentreseptuagintillion", "octingenquattuorseptuagintillion", "octingenquinseptuagintillion", "octingensexseptuagintillion", "octingenseptenseptuagintillion",
	"octingenoctoseptuagintillion", "octingennovemseptuagintillion", "octingenoctogintillion", "octingenunoctogintillion", "octingendooctogintillion", "octingentreoctogintillion", "octingenquattuoroctogintillion",
	"octingenquinoctogintillion", "octingensexoctogintillion", "octingenseptenoctogintillion", "octingenoctooctogintillion", "octingennovemoctogintillion", "octingennonagintillion", "octingenunnonagintillion",
	"octingendononagintillion", "octingentrenonagintillion", "octingenquattuornonagintillion", "octingenquinnonagintillion", "octingensexnonagintillion", "octingenseptennonagintillion", "octingenoctononagintillion",
	"octingennovemnonagintillion", "nongentillion", "nongenuntillion", "nongendotillion", "nongentretillion", "nongenquattuortillion", "nongenquintillion",
	"nongensextillion", "nongenseptentillion", "nongenoctotillion", "nongennovemtillion", "nongendecillion", "nongenundecillion", "nongendodecillion",
	"nongentredecillion", "nongenquattuordecillion", "nongenquindecillion", "nongensexdecillion", "nongenseptendecillion", "nongenoctodecillion", "nongennovemdecillion",
	"nongenvigintillion", "nongenunvigintillion", "nongendovigintillion", "nongentrevigintillion", "nongenquattuorvigintillion", "nongenquinvigintillion", "nongensexvigintillion",
	"nongenseptenvigintillion", "nongenoctovigintillion", "nongennovemvigintillion", "nongentrigintillion", "nongenuntrigintillion", "nongendotrigintillion", "nongentretrigintillion",
	"nongenquattuortrigintillion", "nongenquintrigintillion", "nongensextrigintillion", "nongenseptentrigintillion", "nongenoctotrigintillion", "nongennovemtrigintillion", "nongenquadragintillion",
	"nongenunquadragintillion", "nongendoquadragintillion", "nongentrequadragintillion", "nongenquattuorquadragintillion", "nongenquinquadragintillion", "nongensexquadragintillion", "nongenseptenquadragintillion",
	"nongenoctoquadragintillion", "nongennovemquadragintillion", "nongenquinquagintillion", "nongenunquinquagintillion", "nongendoquinquagintillion", "nongentrequinquagintillion", "nongenquattuorquinquagintillion",
	"nongenquinquinquagintillion", "nongensexquinquagintillion", "nongenseptenquinquagintillion", "nongenoctoquinquagintillion", "nongennovemquinquagintillion", "nongensexagintillion", "nongenunsexagintillion",
	"nongendosexagintillion", "nongentresexagintillion", "nongenquattuorsexagintillion", "nongenquinsexagintillion", "nongensexsexagintillion", "nongenseptensexagintillion", "nongenoctosexagintillion",
	"nongennovemsexagintillion", "nongenseptuagintillion", "nongenunseptuagintillion", "nongendoseptuagintillion", "nongentreseptuagintillion", "nongenquattuorseptuagintillion", "nongenquinseptuagintillion",
	"nongensexseptuagintillion", "nongenseptenseptuagintillion", "nongenoctoseptuagintillion", "nongennovemseptuagintillion", "nongenoctogintillion", "nongenunoctogintillion", "nongendooctogintillion",
	"nongentreoctogintillion", "nongenquattuoroctogintillion", "nongenquinoctogintillion", "nongensexoctogintillion", "nongenseptenoctogintillion", "nongenoctooctogintillion", "nongennovemoctogintillion",
	"nongennonagintillion", "nongenunnonagintillion", "nongendononagintillion", "nongentrenonagintillion", "nongenquattuornonagintillion", "nongenquinnonagintillion", "nongensexnonagintillion",
	"nongenseptennonagintillion", "nongenoctononagintillion", "nongennovemnonagintillion", "milliatillion", "milliauntillion", "milliadotillion", "milliatretillion",
	"milliaquattuortillion", "milliaquintillion", "milliasextillion", "milliaseptentillion", "milliaoctotillion", "millianovemtillion", "milliadecillion",
	"milliaundecillion", "milliadodecillion", "milliatredecillion", "milliaquattuordecillion", "milliaquindecillion", "milliasexdecillion", "milliaseptendecillion",
	"milliaoctodecillion", "millianovemdecillion", "milliavigintillion", "milliaunvigintillion", "milliadovigintillion", "milliatrevigintillion", "milliaquattuorvigintillion",
	"milliaquinvigintillion", "milliasexvigintillion", "milliaseptenvigintillion", "milliaoctovigintillion", "millianovemvigintillion", "milliatrigintillion", "milliauntrigintillion",
	"milliadotrigintillion", "milliatretrigintillion", "milliaquattuortrigintillion", "milliaquintrigintillion", "milliasextrigintillion", "milliaseptentrigintillion", "milliaoctotrigintillion",
	"millianovemtrigintillion", "milliaquadragintillion", "milliaunquadragintillion", "milliadoquadragintillion", "milliatrequadragintillion", "milliaquattuorquadragintillion", "milliaquinquadragintillion",
	"milliasexquadragintillion", "milliaseptenquadragintillion", "milliaoctoquadragintillion", "millianovemquadragintillion", "milliaquinquagintillion", "milliaunquinquagintillion", "milliadoquinquagintillion",
	"milliatrequinquagintillion", "milliaquattuorquinquagintillion", "milliaquinquinquagintillion", "milliasexquinquagintillion", "milliaseptenquinquagintillion", "milliaoctoquinquagintillion", "millianovemquinquagintillion",
	"milliasexagintillion", "milliaunsexagintillion", "milliadosexagintillion", "milliatresexagintillion", "milliaquattuorsexagintillion", "milliaquinsexagintillion", "milliasexsexagintillion",
	"milliaseptensexagintillion", "milliaoctosexagintillion", "millianovemsexagintillion", "milliaseptuagintillion", "milliaunseptuagintillion", "milliadoseptuagintillion", "milliatreseptuagintillion",
	"milliaquattuorseptuagintillion", "milliaquinseptuagintillion", "milliasexseptuagintillion", "milliaseptenseptuagintillion", "milliaoctoseptuagintillion", "millianovemseptuagintillion", "milliaoctogintillion",
	"milliaunoctogintillion", "milliadooctogintillion", "milliatreoctogintillion", "milliaquattuoroctogintillion", "milliaquinoctogintillion", "milliasexoctogintillion", "milliaseptenoctogintillion",
	"milliaoctooctogintillion", "millianovemoctogintillion", "millianonagintillion", "milliaunnonagintillion", "milliadononagintillion", "milliatrenonagintillion", "milliaquattuornonagintillion",
	"milliaquinnonagintillion", "milliasexnonagintillion", "milliaseptennonagintillion", "milliaoctononagintillion", "millianovemnonagintillion", "milliacentillion", "milliacenuntillion",
	"milliacendotillion", "milliacentretillion", "milliacenquattuortillion", "milliacenquintillion", "milliacensextillion", "milliacenseptentillion", "milliacenoctotillion",
	"milliacennovemtillion", "milliacendecillion", "milliacenundecillion", "milliacendodecillion", "milliacentredecillion", "milliacenquattuordecillion", "milliacenquindecillion",
	"milliacensexdecillion", "milliacenseptendecillion", "milliacenoctodecillion", "milliacennovemdecillion", "milliacenvigintillion", "milliacenunvigintillion", "milliacendovigintillion",
	"milliacentrevigintillion", "milliacenquattuorvigintillion", "milliacenquinvigintillion", "milliacensexvigintillion", "milliacenseptenvigintillion", "milliacenoctovigintillion", "milliacennovemvigintillion",
	"milliacentrigintillion", "milliacenuntrigintillion", "milliacendotrigintillion", "milliacentretrigintillion", "milliacenquattuortrigintillion", "milliacenquintrigintillion", "milliacensextrigintillion",
	"milliacenseptentrigintillion", "milliacenoctotrigintillion", "milliacennovemtrigintillion", "milliacenquadragintillion", "milliacenunquadragintillion", "milliacendoquadragintillion", "milliacentrequadragintillion",
	"milliacenquattuorquadragintillion", "milliacenquinquadragintillion", "milliacensexquadragintillion", "milliacenseptenquadragintillion", "milliacenoctoquadragintillion", "milliacennovemquadragintillion", "milliacenquinquagintillion",
	"milliacenunquinquagintillion", "milliacendoquinquagintillion", "milliacentrequinquagintillion", "milliacenquattuorquinquagintillion", "milliacenquinquinquagintillion", "milliacensexquinquagintillion", "milliacenseptenquinquagintillion",
	"milliacenoctoquinquagintillion", "milliacennovemquinquagintillion", "milliacensexagintillion", "milliacenunsexagintillion", "milliacendosexagintillion", "milliacentresexagintillion", "milliacenquattuorsexagintillion",
	"milliacenquinsexagintillion", "milliacensexsexagintillion", "milliacenseptensexagintillion", "milliacenoctosexagintillion", "milliacennovemsexagintillion", "milliacenseptuagintillion", "milliacenunseptuagintillion",
	"milliacendoseptuagintillion", "milliacentreseptuagintillion", "milliacenquattuorseptuagintillion", "milliacenquinseptuagintillion", "milliacensexseptuagintillion", "milliacenseptenseptuagintillion", "milliacenoctoseptuagintillion",
	"milliacennovemseptuagintillion", "milliacenoctogintillion", "milliacenunoctogintillion", "milliacendooctogintillion", "milliacentreoctogintillion", "milliacenquattuoroctogintillion", "milliacenquinoctogintillion",
	"milliacensexoctogintillion", "milliacenseptenoctogintillion", "milliacenoctooctogintillion", "milliacennovemoctogintillion", "milliacennonagintillion", "milliacenunnonagintillion", "milliacendononagintillion",
	"milliacentrenonagintillion", "milliacenquattuornonagintillion", "milliacenquinnonagintillion", "milliacensexnonagintillion", "milliacenseptennonagintillion", "milliacenoctononagintillion", "milliacennovemnonagintillion",
	"milliaducentillion", "milliaducenuntillion", "milliaducendotillion", "milliaducentretillion", "milliaducenquattuortillion", "milliaducenquintillion", "milliaducensextillion",
	"milliaducenseptentillion", "milliaducenoctotillion", "milliaducennovemtillion", "milliaducendecillion", "milliaducenundecillion", "milliaducendodecillion", "milliaducentredecillion",
	"milliaducenquattuordecillion", "milliaducenquindecillion", "milliaducensexdecillion", "milliaducenseptendecillion", "milliaducenoctodecillion", "milliaducennovemdecillion", "milliaducenvigintillion",
	"milliaducenunvigintillion", "milliaducendovigintillion", "milliaducentrevigintillion", "milliaducenquattuorvigintillion", "milliaducenquinvigintillion", "milliaducensexvigintillion", "milliaducenseptenvigintillion",
	"milliaducenoctovigintillion", "milliaducennovemvigintillion", "milliaducentrigintillion", "milliaducenuntrigintillion", "milliaducendotrigintillion", "milliaducentretrigintillion", "milliaducenquattuortrigintillion",
	"milliaducenquintrigintillion", "milliaducensextrigintillion", "milliaducenseptentrigintillion", "milliaducenoctotrigintillion", "milliaducennovemtrigintillion", "milliaducenquadragintillion", "milliaducenunquadragintillion",
	"milliaducendoquadragintillion", "milliaducentrequadragintillion", "milliaducenquattuorquadragintillion", "milliaducenquinquadragintillion", "milliaducensexquadragintillion", "milliaducenseptenquadragintillion", "milliaducenoctoquadragintillion",
	"milliaducennovemquadragintillion", "milliaducenquinquagintillion", "milliaducenunquinquagintillion", "milliaducendoquinquagintillion", "milliaducentrequinquagintillion", "milliaducenquattuorquinquagintillion", "milliaducenquinquinquagintillion",
	"milliaducensexquinquagintillion", "milliaducenseptenquinquagintillion", "milliaducenoctoquinquagintillion", "milliaducennovemquinquagintillion", "milliaducensexagintillion", "milliaducenunsexagintillion", "milliaducendosexagintillion",
	"milliaducentresexagintillion", "milliaducenquattuorsexagintillion", "milliaducenquinsexagintillion", "milliaducensexsexagintillion", "milliaducenseptensexagintillion", "milliaducenoctosexagintillion", "milliaducennovemsexagintillion",
	"milliaducenseptuagintillion", "milliaducenunseptuagintillion", "milliaducendoseptuagintillion", "milliaducentreseptuagintillion", "milliaducenquattuorseptuagintillion", "milliaducenquinseptuagintillion", "milliaducensexseptuagintillion",
	"milliaducenseptenseptuagintillion", "milliaducenoctoseptuagintillion", "milliaducennovemseptuagintillion", "milliaducenoctogintillion", "milliaducenunoctogintillion", "milliaducendooctogintillion", "milliaducentreoctogintillion",
	"milliaducenquattuoroctogintillion", "milliaducenquinoctogintillion", "milliaducensexoctogintillion", "milliaducenseptenoctogintillion", "milliaducenoctooctogintillion", "milliaducennovemoctogintillion", "milliaducennonagintillion",
	"milliaducenunnonagintillion", "milliaducendononagintillion", "milliaducentrenonagintillion", "milliaducenquattuornonagintillion", "milliaducenquinnonagintillion", "milliaducensexnonagintillion", "milliaducenseptennonagintillion",
	"milliaducenoctononagintillion", "milliaducennovemnonagintillion", "milliatrecentillion", "milliatrecenuntillion", "milliatrecendotillion", "milliatrecentretillion", "milliatrecenquattuortillion",
	"milliatrecenquintillion", "milliatrecensextillion", "milliatrecenseptentillion", "milliatrecenoctotillion", "milliatrecennovemtillion", "milliatrecendecillion", "milliatrecenundecillion",
	"milliatrecendodecillion", "milliatrecentredecillion", "milliatrecenquattuordecillion", "milliatrecenquindecillion", "milliatrecensexdecillion", "milliatrecenseptendecillion", "milliatrecenoctodecillion",
	"milliatrecennovemdecillion", "milliatrecenvigintillion", "milliatrecenunvigintillion", "milliatrecendovigintillion", "milliatrecentrevigintillion", "milliatrecenquattuorvigintillion", "milliatrecenquinvigintillion",
	"milliatrecensexvigintillion", "milliatrecenseptenvigintillion", "milliatrecenoctovigintillion", "milliatrecennovemvigintillion", "milliatrecentrigintillion", "milliatrecenuntrigintillion", "milliatrecendotrigintillion",
	"milliatrecentretrigintillion", "milliatrecenquattuortrigintillion", "milliatrecenquintrigintillion", "milliatrecensextrigintillion", "milliatrecenseptentrigintillion", "milliatrecenoctotrigintillion", "milliatrecennovemtrigintillion",
	"milliatrecenquadragintillion", "milliatrecenunquadragintillion", "milliatrecendoquadragintillion", "milliatrecentrequadragintillion", "milliatrecenquattuorquadragintillion", "milliatrecenquinquadragintillion", "milliatrecensexquadragintillion",
	"milliatrecenseptenquadragintillion", "milliatrecenoctoquadragintillion", "milliatrecennovemquadragintillion", "milliatrecenquinquagintillion", "milliatrecenunquinquagintillion", "milliatrecendoquinquagintillion", "milliatrecentrequinquagintillion",
	"milliatrecenquattuorquinquagintillion", "milliatrecenquinquinquagintillion", "milliatrecensexquinquagintillion", "milliatrecenseptenquinquagintillion", "milliatrecenoctoquinquagintillion", "milliatrecennovemquinquagintillion", "milliatrecensexagintillion",
	"milliatrecenunsexagintillion", "milliatrecendosexagintillion", "milliatrecentresexagintillion", "milliatrecenquattuorsexagintillion", "milliatrecenquinsexagintillion", "milliatrecensexsexagintillion", "milliatrecenseptensexagintillion",
	"milliatrecenoctosexagintillion", "milliatrecennovemsexagintillion", "milliatrecenseptuagintillion", "milliatrecenunseptuagintillion", "milliatrecendoseptuagintillion", "milliatrecentreseptuagintillion", "milliatrecenquattuorseptuagintillion",
	"milliatrecenquinseptuagintillion", "milliatrecensexseptuagintillion", "milliatrecenseptenseptuagintillion", "milliatrecenoctoseptuagintillion", "milliatrecennovemseptuagintillion", "milliatrecenoctogintillion", "milliatrecenunoctogintillion",
	"milliatrecendooctogintillion", "milliatrecentreoctogintillion", "milliatrecenquattuoroctogintillion", "milliatrecenquinoctogintillion", "milliatrecensexoctogintillion", "milliatrecenseptenoctogintillion", "milliatrecenoctooctogintillion",
	"milliatrecennovemoctogintillion", "milliatrecennonagintillion", "milliatrecenunnonagintillion", "milliatrecendononagintillion", "milliatrecentrenonagintillion", "milliatrecenquattuornonagintillion", "milliatrecenquinnonagintillion",
	"milliatrecensexnonagintillion", "milliatrecenseptennonagintillion", "milliatrecenoctononagintillion", "milliatrecennovemnonagintillion", "milliaquadringentillion", "milliaquadringenuntillion", "milliaquadringendotillion",
	"milliaquadringentretillion", "milliaquadringenquattuortillion", "milliaquadringenquintillion", "milliaquadringensextillion", "milliaquadringenseptentillion", "milliaquadringenoctotillion", "milliaquadringennovemtillion",
	"milliaquadringendecillion", "milliaquadringenundecillion", "milliaquadringendodecillion", "milliaquadringentredecillion", "milliaquadringenquattuordecillion", "milliaquadringenquindecillion", "milliaquadringensexdecillion",
	"milliaquadringenseptendecillion", "milliaquadringenoctodecillion", "milliaquadringennovemdecillion", "milliaquadringenvigintillion", "milliaquadringenunvigintillion", "milliaquadringendovigintillion", "milliaquadringentrevigintillion",
	"milliaquadringenquattuorvigintillion", "milliaquadringenquinvigintillion", "milliaquadringensexvigintillion", "milliaquadringenseptenvigintillion", "milliaquadringenoctovigintillion", "milliaquadringennovemvigintillion", "milliaquadringentrigintillion",
	"milliaquadringenuntrigintillion", "milliaquadringendotrigintillion", "milliaquadringentretrigintillion", "milliaquadringenquattuortrigintillion", "milliaquadringenquintrigintillion", "milliaquadringensextrigintillion", "milliaquadringenseptentrigintillion",
	"milliaquadringenoctotrigintillion", "milliaquadringennovemtrigintillion", "milliaquadringenquadragintillion", "milliaquadringenunquadragintillion", "milliaquadringendoquadragintillion", "milliaquadringentrequadragintillion", "milliaquadringenquattuorquadragintillion",
	"milliaquadringenquinquadragintillion", "milliaquadringensexquadragintillion", "milliaquadringenseptenquadragintillion", "milliaquadringenoctoquadragintillion", "milliaquadringennovemquadragintillion", "milliaquadringenquinquagintillion", "milliaquadringenunquinquagintillion",
	"milliaquadringendoquinquagintillion", "milliaquadringentrequinquagintillion", "milliaquadringenquattuorquinquagintillion", "milliaquadringenquinquinquagintillion", "milliaquadringensexquinquagintillion", "milliaquadringenseptenquinquagintillion", "milliaquadringenoctoquinquagintillion",
	"milliaquadringennovemquinquagintillion", "milliaquadringensexagintillion", "milliaquadringenunsexagintillion", "milliaquadringendosexagintillion", "milliaquadringentresexagintillion", "milliaquadringenquattuorsexagintillion", "milliaquadringenquinsexagintillion",
	"milliaquadringensexsexagintillion", "milliaquadringenseptensexagintillion", "milliaquadringenoctosexagintillion", "milliaquadringennovemsexagintillion", "milliaquadringenseptuagintillion", "milliaquadringenunseptuagintillion", "milliaquadringendoseptuagintillion",
	"milliaquadringentreseptuagintillion", "milliaquadringenquattuorseptuagintillion", "milliaquadringenquinseptuagintillion", "milliaquadringensexseptuagintillion", "milliaquadringenseptenseptuagintillion", "milliaquadringenoctoseptuagintillion", "milliaquadringennovemseptuagintillion",
	"milliaquadringenoctogintillion", "milliaquadringenunoctogintillion", "milliaquadringendooctogintillion", "milliaquadringentreoctogintillion", "milliaquadringenquattuoroctogintillion", "milliaquadringenquinoctogintillion", "milliaquadringensexoctogintillion",
	"milliaquadringenseptenoctogintillion", "milliaquadringenoctooctogintillion", "milliaquadringennovemoctogintillion", "milliaquadringennonagintillion", "milliaquadringenunnonagintillion", "milliaquadringendononagintillion", "milliaquadringentrenonagintillion",
	"milliaquadringenquattuornonagintillion", "milliaquadringenquinnonagintillion", "milliaquadringensexnonagintillion", "milliaquadringenseptennonagintillion", "milliaquadringenoctononagintillion", "milliaquadringennovemnonagintillion", "milliaquingentillion",
	"milliaquingenuntillion", "milliaquingendotillion", "milliaquingentretillion", "milliaquingenquattuortillion", "milliaquingenquintillion", "milliaquingensextillion", "milliaquingenseptentillion",
	"milliaquingenoctotillion", "milliaquingennovemtillion", "milliaquingendecillion", "milliaquingenundecillion", "milliaquingendodecillion", "milliaquingentredecillion", "milliaquingenquattuordecillion",
	"milliaquingenquindecillion", "milliaquingensexdecillion", "milliaquingenseptendecillion", "milliaquingenoctodecillion", "milliaquingennovemdecillion", "milliaquingenvigintillion", "milliaquingenunvigintillion",
	"milliaquingendovigintillion", "milliaquingentrevigintillion", "milliaquingenquattuorvigintillion", "milliaquingenquinvigintillion", "milliaquingensexvigintillion", "milliaquingenseptenvigintillion", "milliaquingenoctovigintillion",
	"milliaquingennovemvigintillion", "milliaquingentrigintillion", "milliaquingenuntrigintillion", "milliaquingendotrigintillion", "milliaquingentretrigintillion", "milliaquingenquattuortrigintillion", "milliaquingenquintrigintillion",
	"milliaquingensextrigintillion", "milliaquingenseptentrigintillion", "milliaquingenoctotrigintillion", "milliaquingennovemtrigintillion", "milliaquingenquadragintillion", "milliaquingenunquadragintillion", "milliaquingendoquadragintillion",
	"milliaquingentrequadragintillion", "milliaquingenquattuorquadragintillion", "milliaquingenquinquadragintillion", "milliaquingensexquadragintillion", "milliaquingenseptenquadragintillion", "milliaquingenoctoquadragintillion", "milliaquingennovemquadragintillion",
	"milliaquingenquinquagintillion", "milliaquingenunquinquagintillion", "milliaquingendoquinquagintillion", "milliaquingentrequinquagintillion", "milliaquingenquattuorquinquagintillion", "milliaquingenquinquinquagintillion", "milliaquingensexquinquagintillion",
	"milliaquingenseptenquinquagintillion", "milliaquingenoctoquinquagintillion", "milliaquingennovemquinquagintillion", "milliaquingensexagintillion", "milliaquingenunsexagintillion", "milliaquingendosexagintillion", "milliaquingentresexagintillion",
	"milliaquingenquattuorsexagintillion", "milliaquingenquinsexagintillion", "milliaquingensexsexagintillion", "milliaquingenseptensexagintillion", "milliaquingenoctosexagintillion", "milliaquingennovemsexagintillion", "milliaquingenseptuagintillion",
	"milliaquingenunseptuagintillion", "milliaquingendoseptuagintillion", "milliaquingentreseptuagintillion", "milliaquingenquattuorseptuagintillion", "milliaquingenquinseptuagintillion", "milliaquingensexseptuagintillion", "milliaquingenseptenseptuagintillion",
	"milliaquingenoctoseptuagintillion", "milliaquingennovemseptuagintillion", "milliaquingenoctogintillion", "milliaquingenunoctogintillion", "milliaquingendooctogintillion", "milliaquingentreoctogintillion", "milliaquingenquattuoroctogintillion",
	"milliaquingenquinoctogintillion", "milliaquingensexoctogintillion", "milliaquingenseptenoctogintillion", "milliaquingenoctooctogintillion", "milliaquingennovemoctogintillion", "milliaquingennonagintillion", "milliaquingenunnonagintillion",
	"milliaquingendononagintillion", "milliaquingentrenonagintillion", "milliaquingenquattuornonagintillion", "milliaquingenquinnonagintillion", "milliaquingensexnonagintillion", "milliaquingenseptennonagintillion", "milliaquingenoctononagintillion",
	"milliaquingennovemnonagintillion", "milliasescentillion", "milliasescenuntillion", "milliasescendotillion", "milliasescentretillion", "milliasescenquattuortillion", "milliasescenquintillion",
	"milliasescensextillion", "milliasescenseptentillion", "milliasescenoctotillion", "milliasescennovemtillion", "milliasescendecillion", "milliasescenundecillion", "milliasescendodecillion",
	"milliasescentredecillion", "milliasescenquattuordecillion", "milliasescenquindecillion", "milliasescensexdecillion", "milliasescenseptendecillion", "milliasescenoctodecillion", "milliasescennovemdecillion",
	"milliasescenvigintillion", "milliasescenunvigintillion", "milliasescendovigintillion", "milliasescentrevigintillion", "milliasescenquattuorvigintillion", "milliasescenquinvigintillion", "milliasescensexvigintillion",
	"milliasescenseptenvigintillion", "milliasescenoctovigintillion", "milliasescennovemvigintillion", "milliasescentrigintillion", "milliasescenuntrigintillion", "milliasescendotrigintillion", "milliasescentretrigintillion",
	"milliasescenquattuortrigintillion", "milliasescenquintrigintillion", "milliasescensextrigintillion", "milliasescenseptentrigintillion", "milliasescenoctotrigintillion", "milliasescennovemtrigintillion", "milliasescenquadragintillion",
	"milliasescenunquadragintillion", "milliasescendoquadragintillion", "milliasescentrequadragintillion", "milliasescenquattuorquadragintillion", "milliasescenquinquadragintillion", "milliasescensexquadragintillion", "milliasescenseptenquadragintillion",
	"milliasescenoctoquadragintillion", "milliasescennovemquadragintillion", "milliasescenquinquagintillion", "milliasescenunquinquagintillion", "milliasescendoquinquagintillion", "milliasescentrequinquagintillion", "milliasescenquattuorquinquagintillion",
	"milliasescenquinquinquagintillion", "milliasescensexquinquagintillion", "milliasescenseptenquinquagintillion", "milliasescenoctoquinquagintillion", "milliasescennovemquinquagintillion", "milliasescensexagintillion", "milliasescenunsexagintillion",
	"milliasescendosexagintillion", "milliasescentresexagintillion", "milliasescenquattuorsexagintillion", "milliasescenquinsexagintillion", "milliasescensexsexagintillion", "milliasescenseptensexagintillion", "milliasescenoctosexagintillion",
	"milliasescennovemsexagintillion", "milliasescenseptuagintillion", "milliasescenunseptuagintillion", "milliasescendoseptuagintillion", "milliasescentreseptuagintillion", "milliasescenquattuorseptuagintillion", "milliasescenquinseptuagintillion",
	"milliasescensexseptuagintillion", "milliasescenseptenseptuagintillion", "milliasescenoctoseptuagintillion", "milliasescennovemseptuagintillion", "milliasescenoctogintillion", "milliasescenunoctogintillion", "milliasescendooctogintillion",
	"milliasescentreoctogintillion", "milliasescenquattuoroctogintillion", "milliasescenquinoctogintillion", "milliasescensexoctogintillion", "milliasescenseptenoctogintillion", "milliasescenoctooctogintillion", "milliasescennovemoctogintillion",
	"milliasescennonagintillion", "milliasescenunnonagintillion", "milliasescendononagintillion", "milliasescentrenonagintillion", "milliasescenquattuornonagintillion", "milliasescenquinnonagintillion", "milliasescensexnonagintillion",
	"milliasescenseptennonagintillion", "milliasescenoctononagintillion", "milliasescennovemnonagintillion", "milliaseptingentillion", "milliaseptingenuntillion", "milliaseptingendotillion", "milliaseptingentretillion",
	"milliaseptingenquattuortillion", "milliaseptingenquintillion", "milliaseptingensextillion", "milliaseptingenseptentillion", "milliaseptingenoctotillion", "milliaseptingennovemtillion", "milliaseptingendecillion",
	"milliaseptingenundecillion", "milliaseptingendodecillion", "milliaseptingentredecillion", "milliaseptingenquattuordecillion", "milliaseptingenquindecillion", "milliaseptingensexdecillion", "milliaseptingenseptendecillion",
	"milliaseptingenoctodecillion", "milliaseptingennovemdecillion", "milliaseptingenvigintillion", "milliaseptingenunvigintillion", "milliaseptingendovigintillion", "milliaseptingentrevigintillion", "milliaseptingenquattuorvigintillion",
	"milliaseptingenquinvigintillion", "milliaseptingensexvigintillion", "milliaseptingenseptenvigintillion", "milliaseptingenoctovigintillion", "milliaseptingennovemvigintillion", "milliaseptingentrigintillion", "milliaseptingenuntrigintillion",
	"milliaseptingendotrigintillion", "milliaseptingentretrigintillion", "milliaseptingenquattuortrigintillion", "milliaseptingenquintrigintillion", "milliaseptingensextrigintillion", "milliaseptingenseptentrigintillion", "milliaseptingenoctotrigintillion",
	"milliaseptingennovemtrigintillion", "milliaseptingenquadragintillion", "milliaseptingenunquadragintillion", "milliaseptingendoquadragintillion", "milliaseptingentrequadragintillion", "milliaseptingenquattuorquadragintillion", "milliaseptingenquinquadragintillion",
	"milliaseptingensexquadragintillion", "milliaseptingenseptenquadragintillion", "milliaseptingenoctoquadragintillion", "milliaseptingennovemquadragintillion", "milliaseptingenquinquagintillion", "milliaseptingenunquinquagintillion", "milliaseptingendoquinquagintillion",
	"milliaseptingentrequinquagintillion", "milliaseptingenquattuorquinquagintillion", "milliaseptingenquinquinquagintillion", "milliaseptingensexquinquagintillion", "milliaseptingenseptenquinquagintillion", "milliaseptingenoctoquinquagintillion", "milliaseptingennovemquinquagintillion",
	"milliaseptingensexagintillion", "milliaseptingenunsexagintillion", "milliaseptingendosexagintillion", "milliaseptingentresexagintillion", "milliaseptingenquattuorsexagintillion", "milliaseptingenquinsexagintillion", "milliaseptingensexsexagintillion",
	"milliaseptingenseptensexagintillion", "milliaseptingenoctosexagintillion", "milliaseptingennovemsexagintillion", "milliaseptingenseptuagintillion", "milliaseptingenunseptuagintillion", "milliaseptingendoseptuagintillion", "milliaseptingentreseptuagintillion",
	"milliaseptingenquattuorseptuagintillion", "milliaseptingenquinseptuagintillion", "milliaseptingensexseptuagintillion", "milliaseptingenseptenseptuagintillion", "milliaseptingenoctoseptuagintillion", "milliaseptingennovemseptuagintillion", "milliaseptingenoctogintillion",
	"milliaseptingenunoctogintillion", "milliaseptingendooctogintillion", "milliaseptingentreoctogintillion", "milliaseptingenquattuoroctogintillion", "milliaseptingenquinoctogintillion", "milliaseptingensexoctogintillion", "milliaseptingenseptenoctogintillion",
	"milliaseptingenoctooctogintillion", "milliaseptingennovemoctogintillion", "milliaseptingennonagintillion", "milliaseptingenunnonagintillion", "milliaseptingendononagintillion", "milliaseptingentrenonagintillion", "milliaseptingenquattuornonagintillion",
	"milliaseptingenquinnonagintillion", "milliaseptingensexnonagintillion", "milliaseptingenseptennonagintillion", "milliaseptingenoctononagintillion", "milliaseptingennovemnonagintillion", "milliaoctingentillion", "milliaoctingenuntillion",
	"milliaoctingendotillion", "milliaoctingentretillion", "milliaoctingenquattuortillion", "milliaoctingenquintillion", "milliaoctingensextillion", "milliaoctingenseptentillion", "milliaoctingenoctotillion",
	"milliaoctingennovemtillion", "milliaoctingendecillion", "milliaoctingenundecillion", "milliaoctingendodecillion", "milliaoctingentredecillion", "milliaoctingenquattuordecillion", "milliaoctingenquindecillion",
	"milliaoctingensexdecillion", "milliaoctingenseptendecillion", "milliaoctingenoctodecillion", "milliaoctingennovemdecillion", "milliaoctingenvigintillion", "milliaoctingenunvigintillion", "milliaoctingendovigintillion",
	"milliaoctingentrevigintillion", "milliaoctingenquattuorvigintillion", "milliaoctingenquinvigintillion", "milliaoctingensexvigintillion", "milliaoctingenseptenvigintillion", "milliaoctingenoctovigintillion", "milliaoctingennovemvigintillion",
	"milliaoctingentrigintillion", "milliaoctingenuntrigintillion", "milliaoctingendotrigintillion", "milliaoctingentretrigintillion", "milliaoctingenquattuortrigintillion", "milliaoctingenquintrigintillion", "milliaoctingensextrigintillion",
	"milliaoctingenseptentrigintillion", "milliaoctingenoctotrigintillion", "milliaoctingennovemtrigintillion", "milliaoctingenquadragintillion", "milliaoctingenunquadragintillion", "milliaoctingendoquadragintillion", "milliaoctingentrequadragintillion",
	"milliaoctingenquattuorquadragintillion", "milliaoctingenquinquadragintillion", "milliaoctingensexquadragintillion", "milliaoctingenseptenquadragintillion", "milliaoctingenoctoquadragintillion", "milliaoctingennovemquadragintillion", "milliaoctingenquinquagintillion",
	"milliaoctingenunquinquagintillion", "milliaoctingendoquinquagintillion", "milliaoctingentrequinquagintillion", "milliaoctingenquattuorquinquagintillion", "milliaoctingenquinquinquagintillion", "milliaoctingensexquinquagintillion", "milliaoctingenseptenquinquagintillion",
	"milliaoctingenoctoquinquagintillion", "milliaoctingennovemquinquagintillion", "milliaoctingensexagintillion", "milliaoctingenunsexagintillion", "milliaoctingendosexagintillion", "milliaoctingentresexagintillion", "milliaoctingenquattuorsexagintillion",
	"milliaoctingenquinsexagintillion", "milliaoctingensexsexagintillion", "milliaoctingenseptensexagintillion", "milliaoctingenoctosexagintillion", "milliaoctingennovemsexagintillion", "milliaoctingenseptuagintillion", "milliaoctingenunseptuagintillion",
	"milliaoctingendoseptuagintillion", "milliaoctingentreseptuagintillion", "milliaoctingenquattuorseptuagintillion", "milliaoctingenquinseptuagintillion", "milliaoctingensexseptuagintillion", "milliaoctingenseptenseptuagintillion", "milliaoctingenoctoseptuagintillion",
	"milliaoctingennovemseptuagintillion", "milliaoctingenoctogintillion", "milliaoctingenunoctogintillion", "milliaoctingendooctogintillion", "milliaoctingentreoctogintillion", "milliaoctingenquattuoroctogintillion", "milliaoctingenquinoctogintillion",
	"milliaoctingensexoctogintillion", "milliaoctingenseptenoctogintillion", "milliaoctingenoctooctogintillion", "milliaoctingennovemoctogintillion", "milliaoctingennonagintillion", "milliaoctingenunnonagintillion", "milliaoctingendononagintillion",
	"milliaoctingentrenonagintillion", "milliaoctingenquattuornonagintillion", "milliaoctingenquinnonagintillion", "milliaoctingensexnonagintillion", "milliaoctingenseptennonagintillion", "milliaoctingenoctononagintillion", "milliaoctingennovemnonagintillion",
	"millianongentillion", "millianongenuntillion", "millianongendotillion", "millianongentretillion", "millianongenquattuortillion", "millianongenquintillion", "millianongensextillion",
	"millianongenseptentillion", "millianongenoctotillion", "millianongennovemtillion", "millianongendecillion", "millianongenundecillion", "millianongendodecillion", "millianongentredecillion",
	"millianongenquattuordecillion", "millianongenquindecillion", "millianongensexdecillion", "millianongenseptendecillion", "millianongenoctodecillion", "millianongennovemdecillion", "millianongenvigintillion",
	"millianongenunvigintillion", "millianongendovigintillion", "millianongentrevigintillion", "millianongenquattuorvigintillion", "millianongenquinvigintillion", "millianongensexvigintillion", "millianongenseptenvigintillion",
	"millianongenoctovigintillion", "millianongennovemvigintillion", "millianongentrigintillion", "millianongenuntrigintillion", "millianongendotrigintillion", "millianongentretrigintillion", "millianongenquattuortrigintillion",
	"millianongenquintrigintillion", "millianongensextrigintillion", "millianongenseptentrigintillion", "millianongenoctotrigintillion", "millianongennovemtrigintillion", "millianongenquadragintillion", "millianongenunquadragintillion",
	"millianongendoquadragintillion", "millianongentrequadragintillion", "millianongenquattuorquadragintillion", "millianongenquinquadragintillion", "millianongensexquadragintillion", "millianongenseptenquadragintillion", "millianongenoctoquadragintillion",
	"millianongennovemquadragintillion", "millianongenquinquagintillion", "millianongenunquinquagintillion", "millianongendoquinquagintillion", "millianongentrequinquagintillion", "millianongenquattuorquinquagintillion", "millianongenquinquinquagintillion",
	"millianongensexquinquagintillion", "millianongenseptenquinquagintillion", "millianongenoctoquinquagintillion", "millianongennovemquinquagintillion", "millianongensexagintillion", "millianongenunsexagintillion", "millianongendosexagintillion",
	"millianongentresexagintillion", "millianongenquattuorsexagintillion", "millianongenquinsexagintillion", "millianongensexsexagintillion", "millianongenseptensexagintillion", "millianongenoctosexagintillion", "millianongennovemsexagintillion",
	"millianongenseptuagintillion", "millianongenunseptuagintillion", "millianongendoseptuagintillion", "millianongentreseptuagintillion", "millianongenquattuorseptuagintillion", "millianongenquinseptuagintillion", "millianongensexseptuagintillion",
	"millianongenseptenseptuagintillion", "millianongenoctoseptuagintillion", "millianongennovemseptuagintillion", "millianongenoctogintillion", "millianongenunoctogintillion", "millianongendooctogintillion", "millianongentreoctogintillion",
	"millianongenquattuoroctogintillion", "millianongenquinoctogintillion", "millianongensexoctogintillion", "millianongenseptenoctogintillion", "millianongenoctooctogintillion", "millianongennovemoctogintillion", "millianongennonagintillion",
	"millianongenunnonagintillion", "millianongendononagintillion", "millianongentrenonagintillion", "millianongenquattuornonagintillion", "millianongenquinnonagintillion", "millianongensexnonagintillion", "millianongenseptennonagintillion",
	"millianongenoctononagintillion", "millianongennovemnonagintillion", "duomilliatillion", "duomilliauntillion", "duomilliadotillion", "duomilliatretillion", "duomilliaquattuortillion",
	"duomilliaquintillion", "duomilliasextillion", "duomilliaseptentillion", "duomilliaoctotillion", "duomillianovemtillion", "duomilliadecillion", "duomilliaundecillion",
	"duomilliadodecillion", "duomilliatredecillion", "duomilliaquattuordecillion", "duomilliaquindecillion", "duomilliasexdecillion", "duomilliaseptendecillion", "duomilliaoctodecillion",
	"duomillianovemdecillion", "duomilliavigintillion", "duomilliaunvigintillion", "duomilliadovigintillion", "duomilliatrevigintillion", "duomilliaquattuorvigintillion", "duomilliaquinvigintillion",
	"duomilliasexvigintillion", "duomilliaseptenvigintillion", "duomilliaoctovigintillion", "duomillianovemvigintillion", "duomilliatrigintillion", "duomilliauntrigintillion", "duomilliadotrigintillion",
	"duomilliatretrigintillion", "duomilliaquattuortrigintillion", "duomilliaquintrigintillion", "duomilliasextrigintillion", "duomilliaseptentrigintillion", "duomilliaoctotrigintillion", "duomillianovemtrigintillion",
	"duomilliaquadragintillion", "duomilliaunquadragintillion", "duomilliadoquadragintillion", "duomilliatrequadragintillion", "duomilliaquattuorquadragintillion", "duomilliaquinquadragintillion", "duomilliasexquadragintillion",
	"duomilliaseptenquadragintillion", "duomilliaoctoquadragintillion", "duomillianovemquadragintillion", "duomilliaquinquagintillion", "duomilliaunquinquagintillion", "duomilliadoquinquagintillion", "duomilliatrequinquagintillion",
	"duomilliaquattuorquinquagintillion", "duomilliaquinquinquagintillion", "duomilliasexquinquagintillion", "duomilliaseptenquinquagintillion", "duomilliaoctoquinquagintillion", "duomillianovemquinquagintillion", "duomilliasexagintillion",
	"duomilliaunsexagintillion", "duomilliadosexagintillion", "duomilliatresexagintillion", "duomilliaquattuorsexagintillion", "duomilliaquinsexagintillion", "duomilliasexsexagintillion", "duomilliaseptensexagintillion",
	"duomilliaoctosexagintillion", "duomillianovemsexagintillion", "duomilliaseptuagintillion", "duomilliaunseptuagintillion", "duomilliadoseptuagintillion", "duomilliatreseptuagintillion", "duomilliaquattuorseptuagintillion",
	"duomilliaquinseptuagintillion", "duomilliasexseptuagintillion", "duomilliaseptenseptuagintillion", "duomilliaoctoseptuagintillion", "duomillianovemseptuagintillion", "duomilliaoctogintillion", "duomilliaunoctogintillion",
	"duomilliadooctogintillion", "duomilliatreoctogintillion", "duomilliaquattuoroctogintillion", "duomilliaquinoctogintillion", "duomilliasexoctogintillion", "duomilliaseptenoctogintillion", "duomilliaoctooctogintillion",
	"duomillianovemoctogintillion", "duomillianonagintillion", "duomilliaunnonagintillion", "duomilliadononagintillion", "duomilliatrenonagintillion", "duomilliaquattuornonagintillion", "duomilliaquinnonagintillion",
	"duomilliasexnonagintillion", "duomilliaseptennonagintillion", "duomilliaoctononagintillion", "duomillianovemnonagintillion", "duomilliacentillion", "duomilliacenuntillion", "duomilliacendotillion",
	"duomilliacentretillion", "duomilliacenquattuortillion", "duomilliacenquintillion", "duomilliacensextillion", "duomilliacenseptentillion", "duomilliacenoctotillion", "duomilliacennovemtillion",
	"duomilliacendecillion", "duomilliacenundecillion", "duomilliacendodecillion", "duomilliacentredecillion", "duomilliacenquattuordecillion", "duomilliacenquindecillion", "duomilliacensexdecillion",
	"duomilliacenseptendecillion", "duomilliacenoctodecillion", "duomilliacennovemdecillion", "duomilliacenvigintillion", "duomilliacenunvigintillion", "duomilliacendovigintillion", "duomilliacentrevigintillion",
	"duomilliacenquattuorvigintillion", "duomilliacenquinvigintillion", "duomilliacensexvigintillion", "duomilliacenseptenvigintillion", "duomilliacenoctovigintillion", "duomilliacennovemvigintillion", "duomilliacentrigintillion",
	"duomilliacenuntrigintillion", "duomilliacendotrigintillion", "duomilliacentretrigintillion", "duomilliacenquattuortrigintillion", "duomilliacenquintrigintillion", "duomilliacensextrigintillion", "duomilliacenseptentrigintillion",
	"duomilliacenoctotrigintillion", "duomilliacennovemtrigintillion", "duomilliacenquadragintillion", "duomilliacenunquadragintillion", "duomilliacendoquadragintillion", "duomilliacentrequadragintillion", "duomilliacenquattuorquadragintillion",
	"duomilliacenquinquadragintillion", "duomilliacensexquadragintillion", "duomilliacenseptenquadragintillion", "duomilliacenoctoquadragintillion", "duomilliacennovemquadragintillion", "duomilliacenquinquagintillion", "duomilliacenunquinquagintillion",
	"duomilliacendoquinquagintillion", "duomilliacentrequinquagintillion", "duomilliacenquattuorquinquagintillion", "duomilliacenquinquinquagintillion", "duomilliacensexquinquagintillion", "duomilliacenseptenquinquagintillion", "duomilliacenoctoquinquagintillion",
	"duomilliacennovemquinquagintillion", "duomilliacensexagintillion", "duomilliacenunsexagintillion", "duomilliacendosexagintillion", "duomilliacentresexagintillion", "duomilliacenquattuorsexagintillion", "duomilliacenquinsexagintillion",
	"duomilliacensexsexagintillion", "duomilliacenseptensexagintillion", "duomilliacenoctosexagintillion", "duomilliacennovemsexagintillion", "duomilliacenseptuagintillion", "duomilliacenunseptuagintillion", "duomilliacendoseptuagintillion",
	"duomilliacentreseptuagintillion", "duomilliacenquattuorseptuagintillion", "duomilliacenquinseptuagintillion", "duomilliacensexseptuagintillion", "duomilliacenseptenseptuagintillion", "duomilliacenoctoseptuagintillion", "duomilliacennovemseptuagintillion",
	"duomilliacenoctogintillion", "duomilliacenunoctogintillion", "duomilliacendooctogintillion", "duomilliacentreoctogintillion", "duomilliacenquattuoroctogintillion", "duomilliacenquinoctogintillion", "duomilliacensexoctogintillion",
	"duomilliacenseptenoctogintillion", "duomilliacenoctooctogintillion", "duomilliacennovemoctogintillion", "duomilliacennonagintillion", "duomilliacenunnonagintillion", "duomilliacendononagintillion", "duomilliacentrenonagintillion",
	"duomilliacenquattuornonagintillion", "duomilliacenquinnonagintillion", "duomilliacensexnonagintillion", "duomilliacenseptennonagintillion", "duomilliacenoctononagintillion", "duomilliacennovemnonagintillion", "duomilliaducentillion",
	"duomilliaducenuntillion", "duomilliaducendotillion", "duomilliaducentretillion", "duomilliaducenquattuortillion", "duomilliaducenquintillion", "duomilliaducensextillion", "duomilliaducenseptentillion",
	"duomilliaducenoctotillion", "duomilliaducennovemtillion", "duomilliaducendecillion", "duomilliaducenundecillion", "duomilliaducendodecillion", "duomilliaducentredecillion", "duomilliaducenquattuordecillion",
	"duomilliaducenquindecillion", "duomilliaducensexdecillion", "duomilliaducenseptendecillion", "duomilliaducenoctodecillion", "duomilliaducennovemdecillion", "duomilliaducenvigintillion", "duomilliaducenunvigintillion",
	"duomilliaducendovigintillion", "duomilliaducentrevigintillion", "duomilliaducenquattuorvigintillion", "duomilliaducenquinvigintillion", "duomilliaducensexvigintillion", "duomilliaducenseptenvigintillion", "duomilliaducenoctovigintillion",
	"duomilliaducennovemvigintillion", "duomilliaducentrigintillion", "duomilliaducenuntrigintillion", "duomilliaducendotrigintillion", "duomilliaducentretrigintillion", "duomilliaducenquattuortrigintillion", "duomilliaducenquintrigintillion",
	"duomilliaducensextrigintillion", "duomilliaducenseptentrigintillion", "duomilliaducenoctotrigintillion", "duomilliaducennovemtrigintillion", "duomilliaducenquadragintillion", "duomilliaducenunquadragintillion", "duomilliaducendoquadragintillion",
	"duomilliaducentrequadragintillion", "duomilliaducenquattuorquadragintillion", "duomilliaducenquinquadragintillion", "duomilliaducensexquadragintillion", "duomilliaducenseptenquadragintillion", "duomilliaducenoctoquadragintillion", "duomilliaducennovemquadragintillion",
	"duomilliaducenquinquagintillion", "duomilliaducenunquinquagintillion", "duomilliaducendoquinquagintillion", "duomilliaducentrequinquagintillion", "duomilliaducenquattuorquinquagintillion", "duomilliaducenquinquinquagintillion", "duomilliaducensexquinquagintillion",
	"duomilliaducenseptenquinquagintillion", "duomilliaducenoctoquinquagintillion", "duomilliaducennovemquinquagintillion", "duomilliaducensexagintillion", "duomilliaducenunsexagintillion", "duomilliaducendosexagintillion", "duomilliaducentresexagintillion",
	"duomilliaducenquattuorsexagintillion", "duomilliaducenquinsexagintillion", "duomilliaducensexsexagintillion", "duomilliaducenseptensexagintillion", "duomilliaducenoctosexagintillion", "duomilliaducennovemsexagintillion", "duomilliaducenseptuagintillion",
	"duomilliaducenunseptuagintillion", "duomilliaducendoseptuagintillion", "duomilliaducentreseptuagintillion", "duomilliaducenquattuorseptuagintillion", "duomilliaducenquinseptuagintillion", "duomilliaducensexseptuagintillion", "duomilliaducenseptenseptuagintillion",
	"duomilliaducenoctoseptuagintillion", "duomilliaducennovemseptuagintillion", "duomilliaducenoctogintillion", "duomilliaducenunoctogintillion", "duomilliaducendooctogintillion", "duomilliaducentreoctogintillion", "duomilliaducenquattuoroctogintillion",
	"duomilliaducenquinoctogintillion", "duomilliaducensexoctogintillion", "duomilliaducenseptenoctogintillion", "duomilliaducenoctooctogintillion", "duomilliaducennovemoctogintillion", "duomilliaducennonagintillion", "duomilliaducenunnonagintillion",
	"duomilliaducendononagintillion", "duomilliaducentrenonagintillion", "duomilliaducenquattuornonagintillion", "duomilliaducenquinnonagintillion", "duomilliaducensexnonagintillion", "duomilliaducenseptennonagintillion", "duomilliaducenoctononagintillion",
	"duomilliaducennovemnonagintillion", "duomilliatrecentillion", "duomilliatrecenuntillion", "duomilliatrecendotillion", "duomilliatrecentretillion", "duomilliatrecenquattuortillion", "duomilliatrecenquintillion",
	"duomilliatrecensextillion", "duomilliatrecenseptentillion", "duomilliatrecenoctotillion", "duomilliatrecennovemtillion", "duomilliatrecendecillion", "duomilliatrecenundecillion", "duomilliatrecendodecillion",
	"duomilliatrecentredecillion", "duomilliatrecenquattuordecillion", "duomilliatrecenquindecillion", "duomilliatrecensexdecillion", "duomilliatrecenseptendecillion", "duomilliatrecenoctodecillion", "duomilliatrecennovemdecillion",
	"duomilliatrecenvigintillion", "duomilliatrecenunvigintillion", "duomilliatrecendovigintillion", "duomilliatrecentrevigintillion", "duomilliatrecenquattuorvigintillion", "duomilliatrecenquinvigintillion", "duomilliatrecensexvigintillion",
	"duomilliatrecenseptenvigintillion", "duomilliatrecenoctovigintillion", "duomilliatrecennovemvigintillion", "duomilliatrecentrigintillion", "duomilliatrecenuntrigintillion", "duomilliatrecendotrigintillion", "duomilliatrecentretrigintillion",
	"duomilliatrecenquattuortrigintillion", "duomilliatrecenquintrigintillion", "duomilliatrecensextrigintillion", "duomilliatrecenseptentrigintillion", "duomilliatrecenoctotrigintillion", "duomilliatrecennovemtrigintillion", "duomilliatrecenquadragintillion",
	"duomilliatrecenunquadragintillion", "duomilliatrecendoquadragintillion", "duomilliatrecentrequadragintillion", "duomilliatrecenquattuorquadragintillion", "duomilliatrecenquinquadragintillion", "duomilliatrecensexquadragintillion", "duomilliatrecenseptenquadragintillion",
	"duomilliatrecenoctoquadragintillion", "duomilliatrecennovemquadragintillion", "duomilliatrecenquinquagintillion", "duomilliatrecenunquinquagintillion", "duomilliatrecendoquinquagintillion", "duomilliatrecentrequinquagintillion", "duomilliatrecenquattuorquinquagintillion",
	"duomilliatrecenquinquinquagintillion", "duomilliatrecensexquinquagintillion", "duomilliatrecenseptenquinquagintillion", "duomilliatrecenoctoquinquagintillion", "duomilliatrecennovemquinquagintillion", "duomilliatrecensexagintillion", "duomilliatrecenunsexagintillion",
	"duomilliatrecendosexagintillion", "duomilliatrecentresexagintillion", "duomilliatrecenquattuorsexagintillion", "duomilliatrecenquinsexagintillion", "duomilliatrecensexsexagintillion", "duomilliatrecenseptensexagintillion", "duomilliatrecenoctosexagintillion",
	"duomilliatrecennovemsexagintillion", "duomilliatrecenseptuagintillion", "duomilliatrecenunseptuagintillion", "duomilliatrecendoseptuagintillion", "duomilliatrecentreseptuagintillion", "duomilliatrecenquattuorseptuagintillion", "duomilliatrecenquinseptuagintillion",
	"duomilliatrecensexseptuagintillion", "duomilliatrecenseptenseptuagintillion", "duomilliatrecenoctoseptuagintillion", "duomilliatrecennovemseptuagintillion", "duomilliatrecenoctogintillion", "duomilliatrecenunoctogintillion", "duomilliatrecendooctogintillion",
	"duomilliatrecentreoctogintillion", "duomilliatrecenquattuoroctogintillion", "duomilliatrecenquinoctogintillion", "duomilliatrecensexoctogintillion", "duomilliatrecenseptenoctogintillion", "duomilliatrecenoctooctogintillion", "duomilliatrecennovemoctogintillion",
	"duomilliatrecennonagintillion", "duomilliatrecenunnonagintillion", "duomilliatrecendononagintillion", "duomilliatrecentrenonagintillion", "duomilliatrecenquattuornonagintillion", "duomilliatrecenquinnonagintillion", "duomilliatrecensexnonagintillion",
	"duomilliatrecenseptennonagintillion", "duomilliatrecenoctononagintillion", "duomilliatrecennovemnonagintillion", "duomilliaquadringentillion", "duomilliaquadringenuntillion", "duomilliaquadringendotillion", "duomilliaquadringentretillion",
	"duomilliaquadringenquattuortillion", "duomilliaquadringenquintillion", "duomilliaquadringensextillion", "duomilliaquadringenseptentillion", "duomilliaquadringenoctotillion", "duomilliaquadringennovemtillion", "duomilliaquadringendecillion",
	"duomilliaquadringenundecillion", "duomilliaquadringendodecillion", "duomilliaquadringentredecillion", "duomilliaquadringenquattuordecillion", "duomilliaquadringenquindecillion", "duomilliaquadringensexdecillion", "duomilliaquadringenseptendecillion",
	"duomilliaquadringenoctodecillion", "duomilliaquadringennovemdecillion", "duomilliaquadringenvigintillion", "duomilliaquadringenunvigintillion", "duomilliaquadringendovigintillion", "duomilliaquadringentrevigintillion", "duomilliaquadringenquattuorvigintillion",
	"duomilliaquadringenquinvigintillion", "duomilliaquadringensexvigintillion", "duomilliaquadringenseptenvigintillion", "duomilliaquadringenoctovigintillion", "duomilliaquadringennovemvigintillion", "duomilliaquadringentrigintillion", "duomilliaquadringenuntrigintillion",
	"duomilliaquadringendotrigintillion", "duomilliaquadringentretrigintillion", "duomilliaquadringenquattuortrigintillion", "duomilliaquadringenquintrigintillion", "duomilliaquadringensextrigintillion", "duomilliaquadringenseptentrigintillion", "duomilliaquadringenoctotrigintillion",
	"duomilliaquadringennovemtrigintillion", "duomilliaquadringenquadragintillion", "duomilliaquadringenunquadragintillion", "duomilliaquadringendoquadragintillion", "duomilliaquadringentrequadragintillion", "duomilliaquadringenquattuorquadragintillion", "duomilliaquadringenquinquadragintillion",
	"duomilliaquadringensexquadragintillion", "duomilliaquadringenseptenquadragintillion", "duomilliaquadringenoctoquadragintillion", "duomilliaquadringennovemquadragintillion", "duomilliaquadringenquinquagintillion", "duomilliaquadringenunquinquagintillion", "duomilliaquadringendoquinquagintillion",
	"duomilliaquadringentrequinquagintillion", "duomilliaquadringenquattuorquinquagintillion", "duomilliaquadringenquinquinquagintillion", "duomilliaquadringensexquinquagintillion", "duomilliaquadringenseptenquinquagintillion", "duomilliaquadringenoctoquinquagintillion", "duomilliaquadringennovemquinquagintillion",
	"duomilliaquadringensexagintillion", "duomilliaquadringenunsexagintillion", "duomilliaquadringendosexagintillion", "duomilliaquadringentresexagintillion", "duomilliaquadringenquattuorsexagintillion", "duomilliaquadringenquinsexagintillion", "duomilliaquadringensexsexagintillion",
	"duomilliaquadringenseptensexagintillion", "duomilliaquadringenoctosexagintillion", "duomilliaquadringennovemsexagintillion", "duomilliaquadringenseptuagintillion", "duomilliaquadringenunseptuagintillion", "duomilliaquadringendoseptuagintillion", "duomilliaquadringentreseptuagintillion",
	"duomilliaquadringenquattuorseptuagintillion", "duomilliaquadringenquinseptuagintillion", "duomilliaquadringensexseptuagintillion", "duomilliaquadringenseptenseptuagintillion", "duomilliaquadringenoctoseptuagintillion", "duomilliaquadringennovemseptuagintillion", "duomilliaquadringenoctogintillion",
	"duomilliaquadringenunoctogintillion", "duomilliaquadringendooctogintillion", "duomilliaquadringentreoctogintillion", "duomilliaquadringenquattuoroctogintillion", "duomilliaquadringenquinoctogintillion", "duomilliaquadringensexoctogintillion", "duomilliaquadringenseptenoctogintillion",
	"duomilliaquadringenoctooctogintillion", "duomilliaquadringennovemoctogintillion", "duomilliaquadringennonagintillion", "duomilliaquadringenunnonagintillion", "duomilliaquadringendononagintillion", "duomilliaquadringentrenonagintillion", "duomilliaquadringenquattuornonagintillion",
	"duomilliaquadringenquinnonagintillion", "duomilliaquadringensexnonagintillion", "duomilliaquadringenseptennonagintillion", "duomilliaquadringenoctononagintillion", "duomilliaquadringennovemnonagintillion", "duomilliaquingentillion", "duomilliaquingenuntillion",
	"duomilliaquingendotillion", "duomilliaquingentretillion", "duomilliaquingenquattuortillion", "duomilliaquingenquintillion", "duomilliaquingensextillion", "duomilliaquingenseptentillion", "duomilliaquingenoctotillion",
	"duomilliaquingennovemtillion", "duomilliaquingendecillion", "duomilliaquingenundecillion", "duomilliaquingendodecillion", "duomilliaquingentredecillion", "duomilliaquingenquattuordecillion", "duomilliaquingenquindecillion",
	"duomilliaquingensexdecillion", "duomilliaquingenseptendecillion", "duomilliaquingenoctodecillion", "duomilliaquingennovemdecillion", "duomilliaquingenvigintillion", "duomilliaquingenunvigintillion", "duomilliaquingendovigintillion",
	"duomilliaquingentrevigintillion", "duomilliaquingenquattuorvigintillion", "duomilliaquingenquinvigintillion", "duomilliaquingensexvigintillion", "duomilliaquingenseptenvigintillion", "duomilliaquingenoctovigintillion", "duomilliaquingennovemvigintillion",
	"duomilliaquingentrigintillion", "duomilliaquingenuntrigintillion", "duomilliaquingendotrigintillion", "duomilliaquingentretrigintillion", "duomilliaquingenquattuortrigintillion", "duomilliaquingenquintrigintillion", "duomilliaquingensextrigintillion",
	"duomilliaquingenseptentrigintillion", "duomilliaquingenoctotrigintillion", "duomilliaquingennovemtrigintillion", "duomilliaquingenquadragintillion", "duomilliaquingenunquadragintillion", "duomilliaquingendoquadragintillion", "duomilliaquingentrequadragintillion",
	"duomilliaquingenquattuorquadragintillion", "duomilliaquingenquinquadragintillion", "duomilliaquingensexquadragintillion", "duomilliaquingenseptenquadragintillion", "duomilliaquingenoctoquadragintillion", "duomilliaquingennovemquadragintillion", "duomilliaquingenquinquagintillion",
	"duomilliaquingenunquinquagintillion", "duomilliaquingendoquinquagintillion", "duomilliaquingentrequinquagintillion", "duomilliaquingenquattuorquinquagintillion", "duomilliaquingenquinquinquagintillion", "duomilliaquingensexquinquagintillion", "duomilliaquingenseptenquinquagintillion",
	"duomilliaquingenoctoquinquagintillion", "duomilliaquingennovemquinquagintillion", "duomilliaquingensexagintillion", "duomilliaquingenunsexagintillion", "duomilliaquingendosexagintillion", "duomilliaquingentresexagintillion", "duomilliaquingenquattuorsexagintillion",
	"duomilliaquingenquinsexagintillion", "duomilliaquingensexsexagintillion", "duomilliaquingenseptensexagintillion", "duomilliaquingenoctosexagintillion", "duomilliaquingennovemsexagintillion", "duomilliaquingenseptuagintillion", "duomilliaquingenunseptuagintillion",
	"duomilliaquingendoseptuagintillion", "duomilliaquingentreseptuagintillion", "duomilliaquingenquattuorseptuagintillion", "duomilliaquingenquinseptuagintillion", "duomilliaquingensexseptuagintillion", "duomilliaquingenseptenseptuagintillion", "duomilliaquingenoctoseptuagintillion",
	"duomilliaquingennovemseptuagintillion", "duomilliaquingenoctogintillion", "duomilliaquingenunoctogintillion", "duomilliaquingendooctogintillion", "duomilliaquingentreoctogintillion", "duomilliaquingenquattuoroctogintillion", "duomilliaquingenquinoctogintillion",
	"duomilliaquingensexoctogintillion", "duomilliaquingenseptenoctogintillion", "duomilliaquingenoctooctogintillion", "duomilliaquingennovemoctogintillion", "duomilliaquingennonagintillion", "duomilliaquingenunnonagintillion", "duomilliaquingendononagintillion",
	"duomilliaquingentrenonagintillion", "duomilliaquingenquattuornonagintillion", "duomilliaquingenquinnonagintillion", "duomilliaquingensexnonagintillion", "duomilliaquingenseptennonagintillion", "duomilliaquingenoctononagintillion", "duomilliaquingennovemnonagintillion",
	"duomilliasescentillion", "duomilliasescenuntillion", "duomilliasescendotillion", "duomilliasescentretillion", "duomilliasescenquattuortillion", "duomilliasescenquintillion", "duomilliasescensextillion",
	"duomilliasescenseptentillion", "duomilliasescenoctotillion", "duomilliasescennovemtillion", "duomilliasescendecillion", "duomilliasescenundecillion", "duomilliasescendodecillion", "duomilliasescentredecillion",
	"duomilliasescenquattuordecillion", "duomilliasescenquindecillion", "duomilliasescensexdecillion", "duomilliasescenseptendecillion", "duomilliasescenoctodecillion", "duomilliasescennovemdecillion", "duomilliasescenvigintillion",
	"duomilliasescenunvigintillion", "duomilliasescendovigintillion", "duomilliasescentrevigintillion", "duomilliasescenquattuorvigintillion", "duomilliasescenquinvigintillion", "duomilliasescensexvigintillion", "duomilliasescenseptenvigintillion",
	"duomilliasescenoctovigintillion", "duomilliasescennovemvigintillion", "duomilliasescentrigintillion", "duomilliasescenuntrigintillion", "duomilliasescendotrigintillion", "duomilliasescentretrigintillion", "duomilliasescenquattuortrigintillion",
	"duomilliasescenquintrigintillion", "duomilliasescensextrigintillion", "duomilliasescenseptentrigintillion", "duomilliasescenoctotrigintillion", "duomilliasescennovemtrigintillion", "duomilliasescenquadragintillion", "duomilliasescenunquadragintillion",
	"duomilliasescendoquadragintillion", "duomilliasescentrequadragintillion", "duomilliasescenquattuorquadragintillion", "duomilliasescenquinquadragintillion", "duomilliasescensexquadragintillion", "duomilliasescenseptenquadragintillion", "duomilliasescenoctoquadragintillion",
	"duomilliasescennovemquadragintillion", "duomilliasescenquinquagintillion", "duomilliasescenunquinquagintillion", "duomilliasescendoquinquagintillion", "duomilliasescentrequinquagintillion", "duomilliasescenquattuorquinquagintillion", "duomilliasescenquinquinquagintillion",
	"duomilliasescensexquinquagintillion", "duomilliasescenseptenquinquagintillion", "duomilliasescenoctoquinquagintillion", "duomilliasescennovemquinquagintillion", "duomilliasescensexagintillion", "duomilliasescenunsexagintillion", "duomilliasescendosexagintillion",
	"duomilliasescentresexagintillion", "duomilliasescenquattuorsexagintillion", "duomilliasescenquinsexagintillion", "duomilliasescensexsexagintillion", "duomilliasescenseptensexagintillion", "duomilliasescenoctosexagintillion", "duomilliasescennovemsexagintillion",
	"duomilliasescenseptuagintillion", "duomilliasescenunseptuagintillion", "duomilliasescendoseptuagintillion", "duomilliasescentreseptuagintillion", "duomilliasescenquattuorseptuagintillion", "duomilliasescenquinseptuagintillion", "duomilliasescensexseptuagintillion",
	"duomilliasescenseptenseptuagintillion", "duomilliasescenoctoseptuagintillion", "duomilliasescennovemseptuagintillion", "duomilliasescenoctogintillion", "duomilliasescenunoctogintillion", "duomilliasescendooctogintillion", "duomilliasescentreoctogintillion",
	"duomilliasescenquattuoroctogintillion", "duomilliasescenquinoctogintillion", "duomilliasescensexoctogintillion", "duomilliasescenseptenoctogintillion", "duomilliasescenoctooctogintillion", "duomilliasescennovemoctogintillion", "duomilliasescennonagintillion",
	"duomilliasescenunnonagintillion", "duomilliasescendononagintillion", "duomilliasescentrenonagintillion", "duomilliasescenquattuornonagintillion", "duomilliasescenquinnonagintillion", "duomilliasescensexnonagintillion", "duomilliasescenseptennonagintillion",
	"duomilliasescenoctononagintillion", "duomilliasescennovemnonagintillion", "duomilliaseptingentillion", "duomilliaseptingenuntillion", "duomilliaseptingendotillion", "duomilliaseptingentretillion", "duomilliaseptingenquattuortillion",
	"duomilliaseptingenquintillion", "duomilliaseptingensextillion", "duomilliaseptingenseptentillion", "duomilliaseptingenoctotillion", "duomilliaseptingennovemtillion", "duomilliaseptingendecillion", "duomilliaseptingenundecillion",
	"duomilliaseptingendodecillion", "duomilliaseptingentredecillion", "duomilliaseptingenquattuordecillion", "duomilliaseptingenquindecillion", "duomilliaseptingensexdecillion", "duomilliaseptingenseptendecillion", "duomilliaseptingenoctodecillion",
	"duomilliaseptingennovemdecillion", "duomilliaseptingenvigintillion", "duomilliaseptingenunvigintillion", "duomilliaseptingendovigintillion", "duomilliaseptingentrevigintillion", "duomilliaseptingenquattuorvigintillion", "duomilliaseptingenquinvigintillion",
	"duomilliaseptingensexvigintillion", "duomilliaseptingenseptenvigintillion", "duomilliaseptingenoctovigintillion", "duomilliaseptingennovemvigintillion", "duomilliaseptingentrigintillion", "duomilliaseptingenuntrigintillion", "duomilliaseptingendotrigintillion",
	"duomilliaseptingentretrigintillion", "duomilliaseptingenquattuortrigintillion", "duomilliaseptingenquintrigintillion", "duomilliaseptingensextrigintillion", "duomilliaseptingenseptentrigintillion", "duomilliaseptingenoctotrigintillion", "duomilliaseptingennovemtrigintillion",
	"duomilliaseptingenquadragintillion", "duomilliaseptingenunquadragintillion", "duomilliaseptingendoquadragintillion", "duomilliaseptingentrequadragintillion", "duomilliaseptingenquattuorquadragintillion", "duomilliaseptingenquinquadragintillion", "duomilliaseptingensexquadragintillion",
	"duomilliaseptingenseptenquadragintillion", "duomilliaseptingenoctoquadragintillion", "duomilliaseptingennovemquadragintillion", "duomilliaseptingenquinquagintillion", "duomilliaseptingenunquinquagintillion", "duomilliaseptingendoquinquagintillion", "duomilliaseptingentrequinquagintillion",
	"duomilliaseptingenquattuorquinquagintillion", "duomilliaseptingenquinquinquagintillion", "duomilliaseptingensexquinquagintillion", "duomilliaseptingenseptenquinquagintillion", "duomilliaseptingenoctoquinquagintillion", "duomilliaseptingennovemquinquagintillion", "duomilliaseptingensexagintillion",
	"duomilliaseptingenunsexagintillion", "duomilliaseptingendosexagintillion", "duomilliaseptingentresexagintillion", "duomilliaseptingenquattuorsexagintillion", "duomilliaseptingenquinsexagintillion", "duomilliaseptingensexsexagintillion", "duomilliaseptingenseptensexagintillion",
	"duomilliaseptingenoctosexagintillion", "duomilliaseptingennovemsexagintillion", "duomilliaseptingenseptuagintillion", "duomilliaseptingenunseptuagintillion", "duomilliaseptingendoseptuagintillion", "duomilliaseptingentreseptuagintillion", "duomilliaseptingenquattuorseptuagintillion",
	"duomilliaseptingenquinseptuagintillion", "duomilliaseptingensexseptuagintillion", "duomilliaseptingenseptenseptuagintillion", "duomilliaseptingenoctoseptuagintillion", "duomilliaseptingennovemseptuagintillion", "duomilliaseptingenoctogintillion", "duomilliaseptingenunoctogintillion",
	"duomilliaseptingendooctogintillion", "duomilliaseptingentreoctogintillion", "duomilliaseptingenquattuoroctogintillion", "duomilliaseptingenquinoctogintillion", "duomilliaseptingensexoctogintillion", "duomilliaseptingenseptenoctogintillion", "duomilliaseptingenoctooctogintillion",
	"duomilliaseptingennovemoctogintillion", "duomilliaseptingennonagintillion", "duomilliaseptingenunnonagintillion", "duomilliaseptingendononagintillion", "duomilliaseptingentrenonagintillion", "duomilliaseptingenquattuornonagintillion", "duomilliaseptingenquinnonagintillion",
	"duomilliaseptingensexnonagintillion", "duomilliaseptingenseptennonagintillion", "duomilliaseptingenoctononagintillion", "duomilliaseptingennovemnonagintillion", "duomilliaoctingentillion", "duomilliaoctingenuntillion", "duomilliaoctingendotillion",
	"duomilliaoctingentretillion", "duomilliaoctingenquattuortillion", "duomilliaoctingenquintillion", "duomilliaoctingensextillion", "duomilliaoctingenseptentillion", "duomilliaoctingenoctotillion", "duomilliaoctingennovemtillion",
	"duomilliaoctingendecillion", "duomilliaoctingenundecillion", "duomilliaoctingendodecillion", "duomilliaoctingentredecillion", "duomilliaoctingenquattuordecillion", "duomilliaoctingenquindecillion", "duomilliaoctingensexdecillion",
	"duomilliaoctingenseptendecillion", "duomilliaoctingenoctodecillion", "duomilliaoctingennovemdecillion", "duomilliaoctingenvigintillion", "duomilliaoctingenunvigintillion", "duomilliaoctingendovigintillion", "duomilliaoctingentrevigintillion",
	"duomilliaoctingenquattuorvigintillion", "duomilliaoctingenquinvigintillion", "duomilliaoctingensexvigintillion", "duomilliaoctingenseptenvigintillion", "duomilliaoctingenoctovigintillion", "duomilliaoctingennovemvigintillion", "duomilliaoctingentrigintillion",
	"duomilliaoctingenuntrigintillion", "duomilliaoctingendotrigintillion", "duomilliaoctingentretrigintillion", "duomilliaoctingenquattuortrigintillion", "duomilliaoctingenquintrigintillion", "duomilliaoctingensextrigintillion", "duomilliaoctingenseptentrigintillion",
	"duomilliaoctingenoctotrigintillion", "duomilliaoctingennovemtrigintillion", "duomilliaoctingenquadragintillion", "duomilliaoctingenunquadragintillion", "duomilliaoctingendoquadragintillion", "duomilliaoctingentrequadragintillion", "duomilliaoctingenquattuorquadragintillion",
	"duomilliaoctingenquinquadragintillion", "duomilliaoctingensexquadragintillion", "duomilliaoctingenseptenquadragintillion", "duomilliaoctingenoctoquadragintillion", "duomilliaoctingennovemquadragintillion", "duomilliaoctingenquinquagintillion", "duomilliaoctingenunquinquagintillion",
	"duomilliaoctingendoquinquagintillion", "duomilliaoctingentrequinquagintillion", "duomilliaoctingenquattuorquinquagintillion", "duomilliaoctingenquinquinquagintillion", "duomilliaoctingensexquinquagintillion", "duomilliaoctingenseptenquinquagintillion", "duomilliaoctingenoctoquinquagintillion",
	"duomilliaoctingennovemquinquagintillion", "duomilliaoctingensexagintillion", "duomilliaoctingenunsexagintillion", "duomilliaoctingendosexagintillion", "duomilliaoctingentresexagintillion", "duomilliaoctingenquattuorsexagintillion", "duomilliaoctingenquinsexagintillion",
	"duomilliaoctingensexsexagintillion", "duomilliaoctingenseptensexagintillion", "duomilliaoctingenoctosexagintillion", "duomilliaoctingennovemsexagintillion", "duomilliaoctingenseptuagintillion", "duomilliaoctingenunseptuagintillion", "duomilliaoctingendoseptuagintillion",
	"duomilliaoctingentreseptuagintillion", "duomilliaoctingenquattuorseptuagintillion", "duomilliaoctingenquinseptuagintillion", "duomilliaoctingensexseptuagintillion", "duomilliaoctingenseptenseptuagintillion", "duomilliaoctingenoctoseptuagintillion", "duomilliaoctingennovemseptuagintillion",
	"duomilliaoctingenoctogintillion", "duomilliaoctingenunoctogintillion", "duomilliaoctingendooctogintillion", "duomilliaoctingentreoctogintillion", "duomilliaoctingenquattuoroctogintillion", "duomilliaoctingenquinoctogintillion", "duomilliaoctingensexoctogintillion",
	"duomilliaoctingenseptenoctogintillion", "duomilliaoctingenoctooctogintillion", "duomilliaoctingennovemoctogintillion", "duomilliaoctingennonagintillion", "duomilliaoctingenunnonagintillion", "duomilliaoctingendononagintillion", "duomilliaoctingentrenonagintillion",
	"duomilliaoctingenquattuornonagintillion", "duomilliaoctingenquinnonagintillion", "duomilliaoctingensexnonagintillion", "duomilliaoctingenseptennonagintillion", "duomilliaoctingenoctononagintillion", "duomilliaoctingennovemnonagintillion", "duomillianongentillion",
	"duomillianongenuntillion", "duomillianongendotillion", "duomillianongentretillion", "duomillianongenquattuortillion", "duomillianongenquintillion", "duomillianongensextillion", "duomillianongenseptentillion",
	"duomillianongenoctotillion", "duomillianongennovemtillion", "duomillianongendecillion", "duomillianongenundecillion", "duomillianongendodecillion", "duomillianongentredecillion", "duomillianongenquattuordecillion",
	"duomillianongenquindecillion", "duomillianongensexdecillion", "duomillianongenseptendecillion", "duomillianongenoctodecillion", "duomillianongennovemdecillion", "duomillianongenvigintillion", "duomillianongenunvigintillion",
	"duomillianongendovigintillion", "duomillianongentrevigintillion", "duomillianongenquattuorvigintillion", "duomillianongenquinvigintillion", "duomillianongensexvigintillion", "duomillianongenseptenvigintillion", "duomillianongenoctovigintillion",
	"duomillianongennovemvigintillion", "duomillianongentrigintillion", "duomillianongenuntrigintillion", "duomillianongendotrigintillion", "duomillianongentretrigintillion", "duomillianongenquattuortrigintillion", "duomillianongenquintrigintillion",
	"duomillianongensextrigintillion", "duomillianongenseptentrigintillion", "duomillianongenoctotrigintillion", "duomillianongennovemtrigintillion", "duomillianongenquadragintillion", "duomillianongenunquadragintillion", "duomillianongendoquadragintillion",
	"duomillianongentrequadragintillion", "duomillianongenquattuorquadragintillion", "duomillianongenquinquadragintillion", "duomillianongensexquadragintillion", "duomillianongenseptenquadragintillion", "duomillianongenoctoquadragintillion", "duomillianongennovemquadragintillion",
	"duomillianongenquinquagintillion", "duomillianongenunquinquagintillion", "duomillianongendoquinquagintillion", "duomillianongentrequinquagintillion", "duomillianongenquattuorquinquagintillion", "duomillianongenquinquinquagintillion", "duomillianongensexquinquagintillion",
	"duomillianongenseptenquinquagintillion", "duomillianongenoctoquinquagintillion", "duomillianongennovemquinquagintillion", "duomillianongensexagintillion", "duomillianongenunsexagintillion", "duomillianongendosexagintillion", "duomillianongentresexagintillion",
	"duomillianongenquattuorsexagintillion", "duomillianongenquinsexagintillion", "duomillianongensexsexagintillion", "duomillianongenseptensexagintillion", "duomillianongenoctosexagintillion", "duomillianongennovemsexagintillion", "duomillianongenseptuagintillion",
	"duomillianongenunseptuagintillion", "duomillianongendoseptuagintillion", "duomillianongentreseptuagintillion", "duomillianongenquattuorseptuagintillion", "duomillianongenquinseptuagintillion", "duomillianongensexseptuagintillion", "duomillianongenseptenseptuagintillion",
	"duomillianongenoctoseptuagintillion", "duomillianongennovemseptuagintillion", "duomillianongenoctogintillion", "duomillianongenunoctogintillion", "duomillianongendooctogintillion", "duomillianongentreoctogintillion", "duomillianongenquattuoroctogintillion",
	"duomillianongenquinoctogintillion", "duomillianongensexoctogintillion", "duomillianongenseptenoctogintillion", "duomillianongenoctooctogintillion", "duomillianongennovemoctogintillion", "duomillianongennonagintillion", "duomillianongenunnonagintillion",
	"duomillianongendononagintillion", "duomillianongentrenonagintillion", "duomillianongenquattuornonagintillion", "duomillianongenquinnonagintillion", "duomillianongensexnonagintillion", "duomillianongenseptennonagintillion", "duomillianongenoctononagintillion",
	"duomillianongennovemnonagintillion", "tremilliatillion", "tremilliauntillion", "tremilliadotillion", "tremilliatretillion", "tremilliaquattuortillion", "tremilliaquintillion",
	"tremilliasextillion", "tremilliaseptentillion", "tremilliaoctotillion", "tremillianovemtillion", "tremilliadecillion", "tremilliaundecillion", "tremilliadodecillion",
	"tremilliatredecillion", "tremilliaquattuordecillion", "tremilliaquindecillion", "tremilliasexdecillion", "tremilliaseptendecillion", "tremilliaoctodecillion", "tremillianovemdecillion",
	"tremilliavigintillion", "tremilliaunvigintillion", "tremilliadovigintillion", "tremilliatrevigintillion", "tremilliaquattuorvigintillion", "tremilliaquinvigintillion", "tremilliasexvigintillion",
	"tremilliaseptenvigintillion", "tremilliaoctovigintillion", "tremillianovemvigintillion", "tremilliatrigintillion", "tremilliauntrigintillion", "tremilliadotrigintillion", "tremilliatretrigintillion",
	"tremilliaquattuortrigintillion", "tremilliaquintrigintillion", "tremilliasextrigintillion", "tremilliaseptentrigintillion", "tremilliaoctotrigintillion", "tremillianovemtrigintillion", "tremilliaquadragintillion",
	"tremilliaunquadragintillion", "tremilliadoquadragintillion", "tremilliatrequadragintillion", "tremilliaquattuorquadragintillion", "tremilliaquinquadragintillion", "tremilliasexquadragintillion", "tremilliaseptenquadragintillion",
	"tremilliaoctoquadragintillion", "tremillianovemquadragintillion", "tremilliaquinquagintillion", "tremilliaunquinquagintillion", "tremilliadoquinquagintillion", "tremilliatrequinquagintillion", "tremilliaquattuorquinquagintillion",
	"tremilliaquinquinquagintillion", "tremilliasexquinquagintillion", "tremilliaseptenquinquagintillion", "tremilliaoctoquinquagintillion", "tremillianovemquinquagintillion", "tremilliasexagintillion", "tremilliaunsexagintillion",
	"tremilliadosexagintillion", "tremilliatresexagintillion", "tremilliaquattuorsexagintillion", "tremilliaquinsexagintillion", "tremilliasexsexagintillion", "tremilliaseptensexagintillion", "tremilliaoctosexagintillion",
	"tremillianovemsexagintillion", "tremilliaseptuagintillion", "tremilliaunseptuagintillion", "tremilliadoseptuagintillion", "tremilliatreseptuagintillion", "tremilliaquattuorseptuagintillion", "tremilliaquinseptuagintillion",
	"tremilliasexseptuagintillion", "tremilliaseptenseptuagintillion", "tremilliaoctoseptuagintillion", "tremillianovemseptuagintillion", "tremilliaoctogintillion", "tremilliaunoctogintillion", "tremilliadooctogintillion",
	"tremilliatreoctogintillion", "tremilliaquattuoroctogintillion", "tremilliaquinoctogintillion", "tremilliasexoctogintillion", "tremilliaseptenoctogintillion", "tremilliaoctooctogintillion", "tremillianovemoctogintillion",
	"tremillianonagintillion", "tremilliaunnonagintillion", "tremilliadononagintillion", "tremilliatrenonagintillion", "tremilliaquattuornonagintillion", "tremilliaquinnonagintillion", "tremilliasexnonagintillion",
	"tremilliaseptennonagintillion", "tremilliaoctononagintillion", "tremillianovemnonagintillion", "tremilliacentillion", "tremilliacenuntillion", "tremilliacendotillion", "tremilliacentretillion",
	"tremilliacenquattuortillion", "tremilliacenquintillion", "tremilliacensextillion", "tremilliacenseptentillion", "tremilliacenoctotillion", "tremilliacennovemtillion", "tremilliacendecillion",
	"tremilliacenundecillion", "tremilliacendodecillion", "tremilliacentredecillion", "tremilliacenquattuordecillion", "tremilliacenquindecillion", "tremilliacensexdecillion", "tremilliacenseptendecillion",
	"tremilliacenoctodecillion", "tremilliacennovemdecillion", "tremilliacenvigintillion", "tremilliacenunvigintillion", "tremilliacendovigintillion", "tremilliacentrevigintillion", "tremilliacenquattuorvigintillion",
	"tremilliacenquinvigintillion", "tremilliacensexvigintillion", "tremilliacenseptenvigintillion", "tremilliacenoctovigintillion", "tremilliacennovemvigintillion", "tremilliacentrigintillion", "tremilliacenuntrigintillion",
	"tremilliacendotrigintillion", "tremilliacentretrigintillion", "tremilliacenquattuortrigintillion", "tremilliacenquintrigintillion", "tremilliacensextrigintillion", "tremilliacenseptentrigintillion", "tremilliacenoctotrigintillion",
	"tremilliacennovemtrigintillion", "tremilliacenquadragintillion", "tremilliacenunquadragintillion", "tremilliacendoquadragintillion", "tremilliacentrequadragintillion", "tremilliacenquattuorquadragintillion", "tremilliacenquinquadragintillion",
	"tremilliacensexquadragintillion", "tremilliacenseptenquadragintillion", "tremilliacenoctoquadragintillion", "tremilliacennovemquadragintillion", "tremilliacenquinquagintillion", "tremilliacenunquinquagintillion", "tremilliacendoquinquagintillion",
	"tremilliacentrequinquagintillion", "tremilliacenquattuorquinquagintillion", "tremilliacenquinquinquagintillion", "tremilliacensexquinquagintillion", "tremilliacenseptenquinquagintillion", "tremilliacenoctoquinquagintillion", "tremilliacennovemquinquagintillion",
	"tremilliacensexagintillion", "tremilliacenunsexagintillion", "tremilliacendosexagintillion", "tremilliacentresexagintillion", "tremilliacenquattuorsexagintillion", "tremilliacenquinsexagintillion", "tremilliacensexsexagintillion",
	"tremilliacenseptensexagintillion", "tremilliacenoctosexagintillion", "tremilliacennovemsexagintillion", "tremilliacenseptuagintillion", "tremilliacenunseptuagintillion", "tremilliacendoseptuagintillion", "tremilliacentreseptuagintillion",
	"tremilliacenquattuorseptuagintillion", "tremilliacenquinseptuagintillion", "tremilliacensexseptuagintillion", "tremilliacenseptenseptuagintillion", "tremilliacenoctoseptuagintillion", "tremilliacennovemseptuagintillion", "tremilliacenoctogintillion",
	"tremilliacenunoctogintillion", "tremilliacendooctogintillion", "tremilliacentreoctogintillion", "tremilliacenquattuoroctogintillion", "tremilliacenquinoctogintillion", "tremilliacensexoctogintillion", "tremilliacenseptenoctogintillion",
	"tremilliacenoctooctogintillion", "tremilliacennovemoctogintillion", "tremilliacennonagintillion", "tremilliacenunnonagintillion", "tremilliacendononagintillion", "tremilliacentrenonagintillion", "tremilliacenquattuornonagintillion",
	"tremilliacenquinnonagintillion", "tremilliacensexnonagintillion", "tremilliacenseptennonagintillion", "tremilliacenoctononagintillion", "tremilliacennovemnonagintillion", "tremilliaducentillion", "tremilliaducenuntillion",
	"tremilliaducendotillion", "tremilliaducentretillion", "tremilliaducenquattuortillion", "tremilliaducenquintillion", "tremilliaducensextillion", "tremilliaducenseptentillion", "tremilliaducenoctotillion",
	"tremilliaducennovemtillion", "tremilliaducendecillion", "tremilliaducenundecillion", "tremilliaducendodecillion", "tremilliaducentredecillion", "tremilliaducenquattuordecillion", "tremilliaducenquindecillion",
	"tremilliaducensexdecillion", "tremilliaducenseptendecillion", "tremilliaducenoctodecillion", "tremilliaducennovemdecillion", "tremilliaducenvigintillion", "tremilliaducenunvigintillion", "tremilliaducendovigintillion",
	"tremilliaducentrevigintillion", "tremilliaducenquattuorvigintillion", "tremilliaducenquinvigintillion", "tremilliaducensexvigintillion", "tremilliaducenseptenvigintillion", "tremilliaducenoctovigintillion", "tremilliaducennovemvigintillion",
	"tremilliaducentrigintillion", "tremilliaducenuntrigintillion", "tremilliaducendotrigintillion", "tremilliaducentretrigintillion", "tremilliaducenquattuortrigintillion", "tremilliaducenquintrigintillion", "tremilliaducensextrigintillion",
	"tremilliaducenseptentrigintillion", "tremilliaducenoctotrigintillion", "tremilliaducennovemtrigintillion", "tremilliaducenquadragintillion", "tremilliaducenunquadragintillion", "tremilliaducendoquadragintillion", "tremilliaducentrequadragintillion",
	"tremilliaducenquattuorquadragintillion", "tremilliaducenquinquadragintillion", "tremilliaducensexquadragintillion", "tremilliaducenseptenquadragintillion", "tremilliaducenoctoquadragintillion", "tremilliaducennovemquadragintillion", "tremilliaducenquinquagintillion",
	"tremilliaducenunquinquagintillion", "tremilliaducendoquinquagintillion", "tremilliaducentrequinquagintillion", "tremilliaducenquattuorquinquagintillion", "tremilliaducenquinquinquagintillion", "tremilliaducensexquinquagintillion", "tremilliaducenseptenquinquagintillion",
	"tremilliaducenoctoquinquagintillion", "tremilliaducennovemquinquagintillion", "tremilliaducensexagintillion", "tremilliaducenunsexagintillion", "tremilliaducendosexagintillion", "tremilliaducentresexagintillion", "tremilliaducenquattuorsexagintillion",
	"tremilliaducenquinsexagintillion", "tremilliaducensexsexagintillion", "tremilliaducenseptensexagintillion", "tremilliaducenoctosexagintillion", "tremilliaducennovemsexagintillion", "tremilliaducenseptuagintillion", "tremilliaducenunseptuagintillion",
	"tremilliaducendoseptuagintillion", "tremilliaducentreseptuagintillion", "tremilliaducenquattuorseptuagintillion", "tremilliaducenquinseptuagintillion", "tremilliaducensexseptuagintillion", "tremilliaducenseptenseptuagintillion", "tremilliaducenoctoseptuagintillion",
	"tremilliaducennovemseptuagintillion", "tremilliaducenoctogintillion", "tremilliaducenunoctogintillion", "tremilliaducendooctogintillion", "tremilliaducentreoctogintillion", "tremilliaducenquattuoroctogintillion", "tremilliaducenquinoctogintillion",
	"tremilliaducensexoctogintillion", "tremilliaducenseptenoctogintillion", "tremilliaducenoctooctogintillion", "tremilliaducennovemoctogintillion", "tremilliaducennonagintillion", "tremilliaducenunnonagintillion", "tremilliaducendononagintillion",
	"tremilliaducentrenonagintillion", "tremilliaducenquattuornonagintillion", "tremilliaducenquinnonagintillion", "tremilliaducensexnonagintillion", "tremilliaducenseptennonagintillion", "tremilliaducenoctononagintillion", "tremilliaducennovemnonagintillion",
	"tremilliatrecentillion", "tremilliatrecenuntillion", "tremilliatrecendotillion", "tremilliatrecentretillion", "tremilliatrecenquattuortillion", "tremilliatrecenquintillion", "tremilliatrecensextillion",
	"tremilliatrecenseptentillion", "tremilliatrecenoctotillion", "tremilliatrecennovemtillion", "tremilliatrecendecillion", "tremilliatrecenundecillion", "tremilliatrecendodecillion", "tremilliatrecentredecillion",
	"tremilliatrecenquattuordecillion", "tremilliatrecenquindecillion", "tremilliatrecensexdecillion", "tremilliatrecenseptendecillion", "tremilliatrecenoctodecillion", "tremilliatrecennovemdecillion", "tremilliatrecenvigintillion",
	"tremilliatrecenunvigintillion", "tremilliatrecendovigintillion", "tremilliatrecentrevigintillion", "tremilliatrecenquattuorvigintillion", "tremilliatrecenquinvigintillion", "tremilliatrecensexvigintillion", "tremilliatrecenseptenvigintillion",
	"tremilliatrecenoctovigintillion", "tremilliatrecennovemvigintillion", "tremilliatrecentrigintillion", "tremilliatrecenuntrigintillion"
};

const string nones[] = { "0","1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15","16", "17", "18", "19" };
const string ntens[] = { "", "", "20", "30", "40", "50", "60", "70", "80", "90", "100" };

const int nOnes = (sizeof(ones) / sizeof(ones[0]));
const int nTens = (sizeof(tens) / sizeof(tens[0]));
const int nHuns = (sizeof(huns) / sizeof(huns[0]));

CLib::CLib()
{
	for (int iHun = 0, nZero = 3; iHun < nHuns; iHun++, nZero += 3)
	{
		string strZero(nZero, '0');
		strZero = "1" + strZero;
		m_vstrHuns.push_back(strZero);
	}

	for (int iTen = 2; iTen < nTens - 1; ++iTen)
		for (int iOne = 1; iOne < 10; ++iOne)
			m_vstr21to99.push_back(pair<string, string>(tens[iTen] + "-" + ones[iOne], to_string(iTen * 10 + iOne)));
}

CLib::~CLib()
{
}

int CLib::ContractLHS(string strInput, string & strResult)
{
	if (strInput.empty())
		return -1;
	strResult.clear();

	int iResult = 0;
	bool bNegative = false;
	string strNumber;

	vector<string> vstrTokens;
	Split(strInput, vstrTokens);

	bool bFound = false;
	vector<string> vstrNumbers;
	vector<vector<string> > vvstrNumbers;
	for (vector<string>::iterator it = vstrTokens.begin(); it != vstrTokens.end(); ++it)
	{
		bFound = false;
		string strToken = *it;

		// Look from 0-19
		for (int iPos = 0; !bFound && iPos < nOnes; ++iPos)
		{
			bFound = strToken == ones[iPos];
			if (bFound)
				vstrNumbers.push_back(nones[iPos]);
		}

		// Next look in 20-90 in increments of 10
		for (int iPos = 2; !bFound && iPos < nTens; ++iPos)
		{
			bFound = strToken == tens[iPos];
			if (bFound)
				vstrNumbers.push_back(ntens[iPos]);
		}

		// Next look at 21-99 skipping increments of 1 skipping the tens
		for (vector<pair<string, string> >::iterator it = m_vstr21to99.begin(); !bFound && it != m_vstr21to99.end(); ++it)
		{
			bFound = strToken == (*it).first;
			if (bFound)
				vstrNumbers.push_back((*it).second);
		}

		// Look at the big numbers that increase in magnitude. 
		// i.e. Thousand, Million, Billion, etc.
		// Number groups terminate on these
		for (int iPos = 0; !bFound && iPos < nHuns; ++iPos)
		{
			bFound = strToken == huns[iPos];
			if (bFound)
			{
				vstrNumbers.push_back(*(m_vstrHuns.begin() + iPos));
				vvstrNumbers.push_back(vstrNumbers);
				vstrNumbers.clear();
			}
		}

		if (!bFound)
		{
			if (strToken == "Negative")
				bNegative = true;
			else
			{
				iResult = -1;
				break;
			}
		}
	}

	if (bFound && !vstrNumbers.empty())
		vvstrNumbers.push_back(vstrNumbers);

	if (iResult == -1)
		return iResult;

	// Process the number groups
	for (vector<vector<string> >::iterator vvit = vvstrNumbers.begin(); vvit != vvstrNumbers.end(); ++vvit)
	{
		string strGroupNumber = *((*vvit).begin());
		for (vector<string>::iterator vit = (*vvit).begin() + 1; vit != (*vvit).end(); ++vit)
		{
			strNumber = *vit;
			if (strNumber.length() > 2 &&
				*(strNumber.end() - 1) == '0')
				strGroupNumber.append(strNumber.begin() + 1, strNumber.end());
			else
				strGroupNumber.replace(strGroupNumber.end() - strNumber.length(), strGroupNumber.end(), strNumber);
		}

		if (!strResult.empty())
			strResult.replace(strResult.end() - strGroupNumber.length(), strResult.end(), strGroupNumber);
		else
			strResult = strGroupNumber;
	}

	if (bNegative)
		strResult = "-" + strResult;
	return iResult;
}

int CLib::ContractRHS(string strInput, string & strResult)
{
	if (strInput.empty())
		return -1;

	int iResult = 0;

	strResult.clear();

	vector<string> vstrTokens;
	Split(strInput, vstrTokens);

	string strDigit;
	for (vector<string>::iterator vit = vstrTokens.begin(); iResult == 0 && vit != vstrTokens.end(); ++vit)
	{
		iResult = ContractLHS(*vit, strDigit);
		if (iResult == 0)
			strResult += strDigit;
	}

	return iResult;
}

int CLib::ExpandLHS(string strInput, string& strResult)
{
	if (strInput.empty())
		return -1;

	int iResult = 0;
	bool bNegative = false;
	int digs, ld, nd, idx;

	strResult.clear();
	if (*(strInput.begin()) == '-')
	{
		bNegative = true;
		strInput = strInput.substr(1);
	}

start:
	digs = (int)strInput.length() - 1;
	idx = (digs / 3) - 1;
	if (idx < nHuns)
	{
		ld = digs % 3;
		switch (ld)
		{
		case 1:
			nd = 2;
			break;
		case 2:
			nd = 3;
			break;
		default:
			nd = 1;
		}

		string strInput2 = strInput.substr(0, nd);
		int input2, digs2, div, l;
		try
		{
			input2 = stoi(strInput2);
		}
		catch (invalid_argument)
		{
			iResult = -1;
		}

		if (iResult == 0)
		{
			bool b10 = false;
		start2:
			digs2 = 0;
			if (input2 > 0)
				digs2 = (int)(floor(log10((double)input2)));
			div = 1;
			for (l = 0; l < digs2; l++)
				div *= 10;

			if (input2 < 20)
			{
				if (!strResult.empty())
					strResult += (b10 ? "-" : " ");
				strResult += ones[input2];
				b10 = false;
			}
			else if (input2 < 100)
			{
				if (!strResult.empty())
					strResult += " ";
				strResult += tens[input2 / div];
				b10 = true;
				if ((input2 % div) != 0)
				{
					input2 = input2 % div;
					goto start2;
				}
			}
			else if (input2 < 1000)
			{
				if (!strResult.empty())
					strResult += " ";
				strResult += ones[input2 / div] + " " + tens[nTens - 1];
				if ((input2 % div) != 0)
				{
					input2 = input2 % div;
					goto start2;
				}
			}

			if (strInput.length() > 3)
			{
				if (!strResult.empty())
					strResult += " ";
				strResult += huns[idx];
			}

			strInput = strInput.substr(nd);
			strInput.erase(0, strInput.find_first_not_of('0'));
			if (strInput.length())
				goto start;
		}
	}
	else
		iResult = -2;

	if (bNegative && iResult == 0)
		strResult = "Negative " + strResult;
	return iResult;
}

int CLib::ExpandRHS(string strInput, string& strResult)
{
	if (strInput.empty())
		return -1;

	int iResult = 0;
	string strDigit, strDigitResult;

	strResult.clear();

	for (string::iterator it = strInput.begin(); iResult == 0 && it != strInput.end(); ++it)
	{
		strDigit = *it;
		iResult = ExpandLHS(strDigit, strDigitResult);
		if (iResult == 0)
		{
			strResult += strDigitResult;
			if (it + 1 != strInput.end())
				strResult += " ";
		}
	}
	return iResult;
}


int CLib::Contract(string strInput, string & strResult)
{
	if (strInput.empty())
		return -1;
	strResult.clear();

	int iResult = 0;
	string strPoint = " Point ";
	size_t stP1 = strInput.find(strPoint);
	if (stP1 == string::npos)
		iResult = ContractLHS(strInput, strResult);
	else
	{
		string strLhs = strInput.substr(0, stP1);
		iResult = ContractLHS(strLhs, strResult);
		if (iResult == 0)
		{
			string strResult2;
			string strRhs = strInput.substr(stP1 + strPoint.length());
			iResult = ContractRHS(strRhs, strResult2);
			if (iResult == 0)
				strResult += "." + strResult2;
		}
	}

	return iResult;
}

int CLib::Expand(string strInput, string & strResult)
{
	int iResult = 0;
	if (strInput.empty())
		iResult = -1;
	else
	{
		size_t stP1 = strInput.find_first_of('.');
		size_t stP2 = string::npos;
		if (stP1 != string::npos)
		{
			stP2 = strInput.find_first_of('.', stP1 + 1);
			if (stP2 != string::npos)
				iResult = -1;
		}

		if (iResult == 0)
		{
			if (stP1 == string::npos)
				iResult = ExpandLHS(strInput, strResult);
			else
			{
				string strLhs = strInput.substr(0, stP1);
				iResult = ExpandLHS(strLhs, strResult);
				if (iResult == 0)
				{
					string strResult2;
					string strRhs = strInput.substr(stP1 + 1);
					iResult = ExpandRHS(strRhs, strResult2);
					if (iResult == 0)
						strResult += " Point " + strResult2;
				}
			}
		}
	}
	return iResult;
}

void CLib::Split(string strInput, vector<string>& vstrTokens)
{
	if (strInput.empty())
		return;

	std::string strToken;
	size_t ipos;

	do
	{
		ipos = strInput.find(' ');
		if (ipos == string::npos)
			vstrTokens.push_back(strInput);
		else
		{
			strToken = strInput.substr(0, ipos);
			vstrTokens.push_back(strToken);
			ipos = strInput.find(' ');
			if (ipos != string::npos)
				strInput.erase(0, ipos + 1);
		}
	} while (ipos != string::npos);
}

string CLib::WB()
{
	return huns[nHuns - 1];
}
