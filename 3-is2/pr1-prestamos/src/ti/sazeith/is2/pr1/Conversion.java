package ti.sazeith.is2.pr1;

import java.util.Calendar;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public final class Conversion {
	private static final Pattern EMAIL_PATTERN = Pattern.compile("[a-z0-9-._]+@(?:[a-z0-9-_]+\\.)+[a-z]{2,}$");
	private static final Pattern DATE_PATTERN = Pattern.compile("([0-9]{1,2})[^0-9]?([0-9]{1,2})[^0-9]?([0-9]{2}|[0-9]{4})$");

	private Conversion() { }

	public static String parseEmail(String email) {
		email = email.toLowerCase();

		if (!EMAIL_PATTERN.matcher(email).matches()) {
			throw new IllegalArgumentException("Email not valid");
		}
		
		return email;
	}

	public static Calendar parseDate(String date) {
		try {
			Calendar cal = Calendar.getInstance();
			Matcher mtc = DATE_PATTERN.matcher(date);
			if (!mtc.matches()) {
				throw new IllegalArgumentException("Invalid date format");
			}

			int day = Integer.parseInt(mtc.group(1));
			int month = Integer.parseInt(mtc.group(2));

			String yearStr = mtc.group(3);
			int year = Integer.parseInt(yearStr);
			if (yearStr.length() == 2) {
				year += cal.get(Calendar.YEAR) / 100 * 100;
			}

			cal.clear();
			cal.set(year,  month, day);
			return cal;
		} catch (NumberFormatException e) {
			throw new IllegalArgumentException(e);
		}
	}

	public static String unparseDate(Calendar date) {
		return String.format("%02d/%02d/%04d", date.get(Calendar.DAY_OF_MONTH), date.get(Calendar.MONTH), date.get(Calendar.YEAR));
	}
}
