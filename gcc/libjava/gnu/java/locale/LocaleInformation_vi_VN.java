/* LocaleInformation_vi_VN.java
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

public class LocaleInformation_vi_VN extends ListResourceBundle
{
  static final String decimalSeparator = ",";
  static final String groupingSeparator = ".";
  static final String numberFormat = "#,##0.###";
  static final String percentFormat = "#,##0%";
  static final String[] weekdays = { null, "Th\u01B0\u0301 hai ", "Th\u01B0\u0301 ba ", "Th\u01B0\u0301 t\u01B0 ", "Th\u01B0\u0301 n\u0103m ", "Th\u01B0\u0301 s\u00E1u ", "Th\u01B0\u0301 ba\u0309y ", "Chu\u0309 nh\u00E2\u0323t " };

  static final String[] shortWeekdays = { null, "Th 2 ", "Th 3 ", "Th 4 ", "Th 5 ", "Th 6 ", "Th 7 ", "CN " };

  static final String[] shortMonths = { "Thg 1", "Thg 2", "Thg 3", "Thg 4", "Thg 5", "Thg 6", "Thg 7", "Thg 8", "Thg 9", "Thg 10", "Thg 11", "Thg 12", null };

  static final String[] months = { "Th\u00E1ng m\u00F4\u0323t", "Th\u00E1ng hai", "Th\u00E1ng ba", "Th\u00E1ng t\u01B0", "Th\u00E1ng n\u0103m", "Th\u00E1ng s\u00E1u", "Th\u00E1ng ba\u0309y", "Th\u00E1ng t\u00E1m", "Th\u00E1ng ch\u00EDn", "Th\u00E1ng m\u01B0\u01A1\u0300i", "Th\u00E1ng m\u01B0\u01A1\u0300i m\u00F4\u0323t", "Th\u00E1ng m\u01B0\u01A1\u0300i hai", null };

  static final String[] ampms = { "", "" };

  static final String shortDateFormat = "EEEE dd MMM yyyy";
  static final String defaultTimeFormat = "";
  static final String currencySymbol = "\u20AB";
  static final String intlCurrencySymbol = "VND";
  static final String currencyFormat = "#,##0.0000$;-$#,##0.0000";

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
