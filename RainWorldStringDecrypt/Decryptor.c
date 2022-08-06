#include "RainWorldStringDecrypt.h"

static const char encryptString[] = "IA/AF57P16dUz+wU1A/9K00Py47ND+8VBk/GRwEPxPE4D78LMM+WLCkPpQTjT5dJWY+Nhg+PuYNEz6WVOo9DpOoPZ11fT3DuTU9WigSP9yeKT8U+EQ/EghqPxKqbj8AAIA/pihwPzuncT9L2XI/In50PzpJdj9D4nY/CVV3P8/Hdz+VOng/tp56PwAAgD90eHo/ZEZ5P53TeD+57FA/wxcxPyjWFz90awE/6cbdPj6xvj7LUrY+KNaXPnRrgT4kbk8+BvonPgBRAj65qMc91tuRPW7PVD2aeCk/0tFEP9DhaT8AAIA/AACAPwAAgD8AAIA/AACAPwAAgD8AAIA/AACAPwAAgD8AAIA/AACAPwAAgD8AAIA/AACAPwAAgD8AAIA/AACAPxmHeD81oFA/P8swP6SJFz/vHgE/ZXrdPtG30j5HBrY+rCKYPu8egT4sB1A+/WAnPgjqAj6pdsY95g2TPZxOEj9YUik/Vh5FP467aT91kmw/AACAP2QCcD/5gHE/CbNyP+BXdD/4InY/Abx2P8cudz+NoXc/UxR4P9dgeD/f+Xg/pmx5PyEgeT9brXg/d8ZQP4HxMD/mrxc/MUUBP/Ar+j7okvk+3/n4PlUE0z7DubU+MG+YPmvSgD41oFA+9ccmPhCDAz6YRMU9xNMnP7oGQz8zymc/AACAPwAAgD8AAIA/AACAPzsFbT9vi0s/f71MP5iITj+gIU8/ZpRPP+rgTz9uLVA/+xJRP/CJdT9/X1E/PTlRP/N5UD8FPjE/YmMXPzhmFD+sgBM/pOcSP950Ej8H0BA/W634PtpQ0z4/bbU+tLuYPueFgD49OVE+7S4mPhkcBD6DgxA/gq0nP/wsQz/xo2c/VC5qPwAAgD99K20/+85HPxbOLT8eZy4/s+UvP3lYMD+pGEs/Q0ByP88lcz+uY3U/AACAP2w9dT+HVk0/R2QxP8wOLT9Hwiw/BZwsP3m2Kz/t0Co/ohEqPxYsKT9J9hA/12D4Pl6d0z67ILU+OAiZPmM5gD5F0lE+5ZUlPvXHJj9fFUE/wA1kPwAAgD8AAIA/AACAP/k8aD+AeUM/ToVEPx2RRT9nUEY/Z/JKPwEacj8AAIA/AACAPwAAgD8AAIA/AACAP9i+cz93JEw/kE1JPwwBST+ItEg/d4JHP+MDRj+YREU/BMZDP9QFKT8PaRE/UxT4PuLp0z421LQ+vFSZPr7Zfz5Na1I+OcQPP7OhJj+hO0E/fudjP699Zz8AAIA/bVdnP7cWaD+GImk/2HpqP+msaz8tw0Y/6z5LP7/zcT+N/3I/U3JzPwAAgD8a5XM/KnVwPyLcbz8aQ28/0INuP0s3bj/53mw/bflrP1zHaj9MlWk/DF9EPw6TKD8YAhI/S3v3PvIb1T4uO7Q+zYaaPq6nfj5p4iU/TuM/P6/bYj8AAIA/AACAPwAAgD8AAIA/AACAPwAAgD8AAIA/AACAP2Rgaz8Umkk/lvZuPwAAgD8AAIA/AACAPwAAgD8AAIA/AACAPwAAgD8AAIA/AACAPwAAgD8";



static char* EncryptionString()
{
	char* xorString = malloc(sizeof(char) * 1448);
	memcpy(xorString, &encryptString[54], 1447);
	xorString[1447] = '\0';
	return xorString;
}

static void xorDecrypt(char* string, int size, int displace)
{
	displace = abs(displace * 82 + displace / 3 + displace % 322 - displace % 17 - displace * 7 % 811);
	char* encryptString = EncryptionString();
	int i = 0;
	int strLength = strlen(encryptString);
	for  (i = 0; i < size; i++)
	{
		string[i] = (string[i] ^ encryptString[(i + displace) % strLength]);
	}
	free(encryptString);
}



void DecryptFile(char filepath[])
{
	FILE* fp;
	int fileSize;
	char* buffer;
	int fileID = 0;

	char* p = filepath;
	while (*p)
	{
		if (isdigit(*p))
		{
			fileID = strtol(p, &p, 10);
			printf("File ID is %ld\n", fileID);
		}
		else
			p++;
	}

	printf("Reading file: %s\n", filepath);

	/*Read file*/
	fopen_s(&fp, filepath, "rb");
	if (!fp) perror("Could not open file: "), exit(1);

	fseek(fp, 0L, SEEK_END);
	fileSize = ftell(fp);
	rewind(fp);

	/* allocate memory for entire content */
	buffer = malloc(fileSize);

	/* copy the file into the buffer */
	if (fread(buffer,1, fileSize, fp) != fileSize)
		fclose(fp), free(buffer), perror("File read failed: "), exit(1);

	fclose(fp);
	/*Read file end*/

	xorDecrypt(buffer, fileSize, fileID + 54);

	fwrite(buffer, 1, fileSize, stdout);
	printf("\n");

	free(buffer);

}

