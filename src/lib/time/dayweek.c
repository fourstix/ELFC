int dayofweek(int year, char month, char day) {
	char monthTable[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };

	year -= (int)((month < 3) ? 1 : 0);

	return  ((year + year / 4 - year / 100 + year / 400 + monthTable[month - 1] + day) % 7);
}



int isleapyear(int year) {
	return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}



int dayofyear(int year, char month, char day) {
	int days[] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };

	if (isleapyear(year) && month >= 2)
		return days[month - 1] + day + 1;

	return days[month - 1] + day;
}

								
