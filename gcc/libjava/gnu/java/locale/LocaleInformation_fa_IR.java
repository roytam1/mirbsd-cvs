/* LocaleInformation_fa_IR.java
   Copyright (C) 2002 Free Software Foundation, Inc.

This file is part of GNU Classpath.

GNU Classpath is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GNU Classpath is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU Classpath; see the file COPYING.  If not, write to the
Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
02111-1307 USA.

Linking this library statically or dynamically with other modules is
making a combined work based on this library.  Thus, the terms and
conditions of the GNU General Public License cover the whole
combination.

As a special exception, the copyright holders of this library give you
permission to link this library with independent modules to produce an
executable, regardless of the license terms of these independent
modules, and to copy and distribute the resulting executable under
terms of your choice, provided that you also meet, for each linked
independent module, the terms and conditions of the license of that
module.  An independent module is a module which is not derived from
or based on this library.  If you modify this library, you may extend
this exception to your version of the library, but you are not
obligated to do so.  If you do not wish to do so, delete this
exception statement from your version. */


// This file was automatically generated by localedef.

package gnu.java.locale;

import java.util.ListResourceBundle;

public class LocaleInformation_fa_IR extends ListResourceBundle
{
  static final String decimalSeparator = "\u066B";
  static final String groupingSeparator = "\u066C";
  static final String numberFormat = "#,##0.###";
  static final String percentFormat = "#,##0%";
  static final String[] weekdays = { null, "\u06CC\u06A9\u200C\u0634\u0646\u0628\u0647", "\u062F\u0648\u0634\u0646\u0628\u0647", "\u0633\u0647\u200C\u0634\u0646\u0628\u0647", "\u0686\u0647\u0627\u0631\u0634\u0646\u0628\u0647", "\u067E\u0646\u062C\u200C\u0634\u0646\u0628\u0647", "\u062C\u0645\u0639\u0647", "\u0634\u0646\u0628\u0647" };

  static final String[] shortWeekdays = { null, "\u06CC.", "\u062F.", "\u0633.", "\u0686.", "\u067E.", "\u062C.", "\u0634." };

  static final String[] shortMonths = { "\u0698\u0627\u0646", "\u0641\u0648\u0631", "\u0645\u0627\u0631", "\u0622\u0648\u0631", "\u0645\u0640\u0647", "\u0698\u0648\u0646", "\u0698\u0648\u06CC", "\u0627\u0648\u062A", "\u0633\u067E\u062A", "\u0627\u0643\u062A", "\u0646\u0648\u0627", "\u062F\u0633\u0627", null };

  static final String[] months = { "\u0698\u0627\u0646\u0648\u06CC\u0647", "\u0641\u0648\u0631\u06CC\u0647", "\u0645\u0627\u0631\u0633", "\u0622\u0648\u0631\u06CC\u0644", "\u0645\u0647", "\u0698\u0648\u0626\u0646", "\u0698\u0648\u0626\u06CC\u0647", "\u0627\u0648\u062A", "\u0633\u067E\u062A\u0627\u0645\u0628\u0631", "\u0627\u0643\u062A\u0628\u0631", "\u0646\u0648\u0627\u0645\u0628\u0631", "\u062F\u0633\u0627\u0645\u0628\u0631", null };

  static final String[] ampms = { "\u0635\u0628\u062D", "\u0639\u0635\u0631" };

  static final String shortDateFormat = "yyyy/MM/dd";
  static final String defaultTimeFormat = "hh:m:s a";
  static final String currencySymbol = "\u0631\u06CC\u0627\u0644";
  static final String intlCurrencySymbol = "IRR";
  static final String currencyFormat = "#,##0. $;-#,##0. $";

  private static final Object[][] contents =
  {
    { "weekdays", weekdays },
    { "shortWeekdays", shortWeekdays },
    { "shortMonths", shortMonths },
    { "months", months },
    { "ampms", ampms },
    { "shortDateFormat", shortDateFormat },
    { "defaultTimeFormat", defaultTimeFormat },
    { "currencySymbol", currencySymbol },
    { "intlCurrencySymbol", intlCurrencySymbol },
    { "currencyFormat", currencyFormat },
    { "decimalSeparator", decimalSeparator },
    { "groupingSeparator", groupingSeparator },
    { "numberFormat", numberFormat },
    { "percentFormat", percentFormat },
  };

  public Object[][] getContents () { return contents; }
}
