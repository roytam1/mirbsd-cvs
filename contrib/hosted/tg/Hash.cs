/* $MirOS: contrib/hosted/tg/Hash.cs,v 1.1 2011/07/18 01:12:07 tg Exp $ */

/*XXX need C# and Perl impl of BAFH (got C and mksh, atm) */

using System;
using System.Security.Cryptography;
using System.Drawing;

public class Rand : System.Random
{
	RandomNumberGenerator rng = new RNGCryptoServiceProvider();
	byte[] b = new byte[4];

	protected override double Sample()
	{
		rng.GetBytes(b);
		uint u = BitConverter.ToUInt32(b, 0);
		return u / (uint.MaxValue + 1.0);
	}
}

class ConsoleApp
{
	static Rand rand = new Rand();

	[STAThread]
	static void Main(string[] args)
	{
		HashFunction hf = new NZAATHash();
		AvalancheTest(hf);
		BitCorrelationTest(hf);
		BucketTest(hf);
		Console.Write("\r\n>");
		Console.ReadLine();
	}

	private static void GenerateSBox()
	{
		byte[] b = new byte[4];
		for (int i = 0; i < 256; i++)
		{
			rand.NextBytes(b);
			uint s = BitConverter.ToUInt32(b, 0);
			Console.Write("0x{0:X8}, ", s);
			if (i % 4 == 3)
				Console.WriteLine();
		}
	}

	static void BitCorrelationTest(HashFunction hf)
	{
		int[,] H = new int[32, 32];
		for (int i=0; i<10000; i++)
		{
			byte[] key = null;
			switch (rand.Next(3))
			{
				case 0:
					key = HashFunction.GetUniformKey();
					break;
				case 1:
					key = HashFunction.GetTextKey();
					break;
				case 2:
					key = HashFunction.GetSparseKey();
					break;
			}
			uint hash = hf.ComputeHash(key);
			for (int j=0; j<32; j++)
				for (int k=0; k<32; k++)
				{
					if (((hash & (1U << j)) != 0) == ((hash & (1U << k)) != 0))
						H[j, k]++;
					else
						H[j, k]--;
				}
		}

		using (Bitmap bmp = new Bitmap(255, 255))
		using (Graphics g = Graphics.FromImage(bmp))
		{
			g.DrawLine(Pens.Black, 63, 0, 63, 255);
			g.DrawLine(Pens.Black, 127, 0, 127, 255);
			g.DrawLine(Pens.Black, 191, 0, 191, 255);
			g.DrawLine(Pens.Black, 0, 63, 255, 63);
			g.DrawLine(Pens.Black, 0, 127, 255, 127);
			g.DrawLine(Pens.Black, 0, 191, 255, 191);
			for (int j=0; j<32; j++)
				for (int k=0; k<32; k++)
				{
					Brush br;
					if (H[j,k]<-233)
						br = Brushes.Red;
					else if (H[j,k]<-199)
						br = Brushes.Orange;
					else if (H[j,k]<199)
						br = Brushes.LightGray;
					else if (H[j,k]>233)
						br = Brushes.GreenYellow;
					else 
						br = Brushes.YellowGreen;
					g.FillRectangle(br, 8*j + 1, 8*k + 1, 5, 5);
				}
			bmp.Save(hf.ToString() + "-bits.gif");
		}
	}

	static int[,] matrix;

	static void InitMatrix(int width)
	{
		matrix = new int[width, 32];
	}

	static void Tally(HashFunction hf, byte[] key)
	{
		uint h0 = hf.ComputeHash(key);
		if (key.Length <= 6)
		{
			for (int i=0; i<key.Length; i++)
				for (int j=0; j<8; j++)
				{
					key[i] ^= (byte) (1 << j);
					uint h1 = hf.ComputeHash(key) ^ h0;
					key[i] ^= (byte) (1 << j);
					int x = i*8 + j;
					for (int y=0; y<32; y++)
					{
						if ((h1 & 1) != 0)
							matrix[x, y]++;
						h1 >>= 1;
					}
				}
		}
		else
		{
			for (int j=0; j<8; j++)
			{
				key[0] ^= (byte) (1 << j);
				uint h1 = hf.ComputeHash(key) ^ h0;
				key[0] ^= (byte) (1 << j);
				for (int y=0; y<32; y++)
				{
					if ((h1 & 1) != 0)
						matrix[j, y]++;
					h1 >>= 1;
				}
				key[key.Length - 1] ^= (byte) (1 << j);
				h1 = hf.ComputeHash(key) ^ h0;
				key[key.Length - 1] ^= (byte) (1 << j);
				for (int y=0; y<32; y++)
				{
					if ((h1 & 1) != 0)
						matrix[j + 8, y]++;
					h1 >>= 1;
				}
			}
		}
	}

	static void RenderMatrix(Graphics g, uint trials)
	{
		int sc = 8;
		uint o3 = trials / 3;
		uint t3 = trials * 2 / 3;
		for (int x=0; x<matrix.GetLength(0); x++)
			for (int y=0; y<matrix.GetLength(1); y++)
			{
				Brush br;
				if (matrix[x, y] == 0 || matrix[x, y] == trials)
					br = Brushes.Red;
				else if (matrix[x, y] < o3 || matrix[x, y] > t3)
					br = Brushes.Orange;
				else
					br = Brushes.Green;
				g.FillRectangle(br, sc * (matrix.GetLength(1) - 1 - y) + 1, sc * x + 1, sc - 3, sc - 3);
			}
	}

	static void AvalancheTest(HashFunction hf)
	{
		int sc = 8;

		Console.WriteLine("\r\n{0}", hf);

		Console.WriteLine("\r\nTwo-octet keys");
		using (Bitmap bmp = new Bitmap(32 * sc - 1, 16 * sc - 1))
		using (Graphics g = Graphics.FromImage(bmp))
		{
			g.DrawLine(Pens.Black, 8*sc-1, 0, 8*sc-1, 16*sc-1);
			g.DrawLine(Pens.Black, 16*sc-1, 0, 16*sc-1, 16*sc-1);
			g.DrawLine(Pens.Black, 24*sc-1, 0, 24*sc-1, 16*sc-1);
			InitMatrix(16);
			byte[] key = new byte[2];
			for (int i=0; i<65536; i++)
			{
				key[0] = (byte) (i & 0xFF);
				key[1] = (byte) (i >> 8);
				Tally(hf, key);
			}
			RenderMatrix(g, 65536);
			bmp.Save(hf.ToString() + "-2.gif");
		}

		RandomNumberGenerator rng = new RNGCryptoServiceProvider();
		Console.WriteLine("Four-octet keys");
		using (Bitmap bmp = new Bitmap(32 * sc - 1, 32 * sc - 1))
		using (Graphics g = Graphics.FromImage(bmp))
		{
			g.DrawLine(Pens.Black, 8 * sc - 1, 0, 8 * sc - 1, 32 * sc - 1);
			g.DrawLine(Pens.Black, 16 * sc - 1, 0, 16 * sc - 1, 32 * sc - 1);
			g.DrawLine(Pens.Black, 24 * sc - 1, 0, 24 * sc - 1, 32 * sc - 1);
			InitMatrix(32);
			byte[] key = new byte[4];
			uint trials = 32768;
			for (int i = 0; i < trials; i++)
			{
				rng.GetBytes(key);
				Tally(hf, key);
			}
			RenderMatrix(g, trials);
			bmp.Save(hf.ToString() + "-4.gif");
		}

		Console.WriteLine("Five-octet keys");
		using (Bitmap bmp = new Bitmap(32 * sc - 1, 40 * sc - 1))
		using (Graphics g = Graphics.FromImage(bmp))
		{
			g.DrawLine(Pens.Black, 8 * sc - 1, 0, 8 * sc - 1, 40 * sc - 1);
			g.DrawLine(Pens.Black, 16 * sc - 1, 0, 16 * sc - 1, 40 * sc - 1);
			g.DrawLine(Pens.Black, 24 * sc - 1, 0, 24 * sc - 1, 40 * sc - 1);
			InitMatrix(40);
			byte[] key = new byte[5];
			uint trials = 32768;
			for (int i = 0; i < trials; i++)
			{
				rng.GetBytes(key);
				Tally(hf, key);
			}
			RenderMatrix(g, trials);
			bmp.Save(hf.ToString() + "-5.gif");
		}

		Console.WriteLine("Three-octet keys");
		using (Bitmap bmp = new Bitmap(32 * sc - 1, 24 * sc - 1))
		using (Graphics g = Graphics.FromImage(bmp))
		{
			g.DrawLine(Pens.Black, 8 * sc - 1, 0, 8 * sc - 1, 24 * sc - 1);
			g.DrawLine(Pens.Black, 16 * sc - 1, 0, 16 * sc - 1, 24 * sc - 1);
			g.DrawLine(Pens.Black, 24 * sc - 1, 0, 24 * sc - 1, 24 * sc - 1);
			InitMatrix(40);
			byte[] key = new byte[3];
			uint trials = 32768;
			for (int i = 0; i < trials; i++)
			{
				rng.GetBytes(key);
				Tally(hf, key);
			}
			RenderMatrix(g, trials);
			bmp.Save(hf.ToString() + "-3.gif");
		}

		rng = new RNGCryptoServiceProvider();
		Console.WriteLine("256-octet keys");
		using (Bitmap bmp = new Bitmap(32 * sc - 1, 16 * sc - 1))
		using (Graphics g = Graphics.FromImage(bmp))
		{
			g.DrawLine(Pens.Black, 8*sc-1, 0, 8*sc-1, 16*sc-1);
			g.DrawLine(Pens.Black, 16*sc-1, 0, 16*sc-1, 16*sc-1);
			g.DrawLine(Pens.Black, 24*sc-1, 0, 24*sc-1, 16*sc-1);
			InitMatrix(16);
			byte[] key = new byte[256];
			uint trials = 32768;
			for (int i=0; i<trials; i++)
			{
				rng.GetBytes(key);
				Tally(hf, key);
			}
			RenderMatrix(g, trials);
			bmp.Save(hf.ToString() + "-256.gif");
		}
	}

	static void BucketTest(HashFunction hf)
	{
		GetRandomKey[] keyfunc = {
			new GetRandomKey(HashFunction.GetUniformKey),
			new GetRandomKey(HashFunction.GetTextKey),
			new GetRandomKey(HashFunction.GetSparseKey),
		};

		Console.WriteLine("\r\n{0}", hf);
		Console.WriteLine("\r\n      Uniform keys    Text keys     Sparse keys");
		Console.WriteLine("\r\nBits  Lower  Upper   Lower  Upper   Lower  Upper");
		for (int bits=1; bits<=16; bits++)
		{
			Console.Write("{0,2} ", bits);
			foreach (GetRandomKey getKey in keyfunc)
			{
				Console.Write(" ");
				uint mask = (1U << bits) - 1U;
				int E = 100;
				for (int lsb=0; lsb<32; lsb += 32-bits)
				{
					if (hf is FNV)
					{
						if (lsb == 0)
							hf = new FNV(bits);
						else
							hf = new FNV();
					}
					int[] buckets = new int[1 << bits];
					int n = E * buckets.Length;
					for (int i=0; i<n; i++)
					{
						byte[] key = getKey();
						uint hash = hf.ComputeHash(key);
						uint bucket = (hash >> lsb) & mask;
						buckets[bucket]++;
					}
					double X = 0.0;
					double p;
					for (int i=0; i<buckets.Length; i++)
					{
						double err = buckets[i] - E;
						X += err * err / E;
						p = buckets[i] / (double)n;
					}
					p = ChiSq(X, buckets.Length - 1);
					Console.Write("  {0:0.000}", p);
				}
			}
			Console.WriteLine();
		}
	}

	static double ChiSq(double x, int n)
	{
		double q, t, p;
		int k, a;

		if (n == 1 && x > 1000) 
			return 0.0;

		if (x > 1000 || n > 1000) 
		{
			q = ChiSq((x - n) * (x - n) / (2 * n), 1) / 2;
			if (x > n) 
				return q;
			else
				return 1 - q;
		}

		p = Math.Exp(-0.5 * x); 
		if ((n % 2) == 1) 
		{ 
			p *= Math.Sqrt(2 * x / Math.PI); 
		}

		k = n;
		while (k >= 2) 
		{ 
			p *= x / k; 
			k -= 2;
		}

		t = p;
		q = -1;
		a = n; 
		while (q != p) 
		{ 
			a += 2;
			t *= x /a; 
			q = p;
			p += t;
		}
		if (p > 1)
			p = 1;

		return 1 - p;
	}
}

public delegate byte[] GetRandomKey();

public abstract class HashFunction
{
	static RandomNumberGenerator rng = new RNGCryptoServiceProvider();
	static byte[] b = new byte[4];

	public abstract uint ComputeHash(byte[] data);

	private static int GetRandomLength()
	{
		rng.GetBytes(b);
        uint s = BitConverter.ToUInt32(b, 0);
		double x = 1 - s / (uint.MaxValue + 1.0);
		return (int) Math.Floor(Math.Sqrt(-800.0 * Math.Log(x)));
	}

	public static byte[] GetUniformKey()
	{
		// with 8 bits/byte we need at least two octets 
		int length = GetRandomLength() + 2;
		byte[] key = new byte[length];
		rng.GetBytes(key);
		return key;
	}

	public static byte[] GetTextKey()
	{
		// with 4.34 bits/byte we need at least 4 octets 
		int length = GetRandomLength() + 4;
		byte[] key = new byte[length];
		rng.GetBytes(key);
		for (int i=0; i<length; i++)
			key[i] = (byte) (65 + (key[i] * key[i] * 26) / 65026);
		return key;
	}

	public static byte[] GetSparseKey()
	{
		// with 3 bits/byte we need at least 6 octets 
		int length = GetRandomLength() + 6;
		byte[] key = new byte[length];
		rng.GetBytes(key);
		for (int i=0; i<length; i++)
			key[i] = (byte)(1 << (key[i] & 7));
		return key;
	}
}

public class SimpleHash : HashFunction
{
	public override uint ComputeHash(byte[] data)
	{
		uint hash = 1;
		foreach (byte b in data)
			hash = (hash + b) * 0x50003;
		return hash;
	}
}

public class FakeHash : HashFunction
{
	RandomNumberGenerator rng = new RNGCryptoServiceProvider();
	byte[] b = new byte[4];

	public override uint ComputeHash(byte[] data)
	{
		rng.GetBytes(b);
		return (uint) (b[0] + 256U * b[1] + 65536U * b[2] + 16777216U * b[3]);
	}
}

public class FNV : HashFunction
{
	int shift;
	uint mask;

	public FNV()
	{
		shift = 0;
		mask = 0xFFFFFFFF;
	}

	public FNV(int bits)
	{
		shift = 32 - bits;
		mask = (1U << shift) - 1U;
	}

	public override uint ComputeHash(byte[] data)
	{
		uint hash = 2166136261;
		foreach (byte b in data)
			hash = (hash * 16777619) ^ b;
		if (shift == 0)
			return hash;
		else
			return (hash ^ (hash >> shift)) & mask;
	}
}

public class ModifiedFNV : HashFunction
{
	public override uint ComputeHash(byte[] data)
	{
		const uint p = 16777619;
		uint hash = 2166136261;
		foreach (byte b in data)
			hash = (hash ^ b) * p;
		hash += hash << 13;
		hash ^= hash >> 7;
		hash += hash << 3;
		hash ^= hash >> 17;
		hash += hash << 5;
		return hash;
	}
}

public class Jenkins96 : HashFunction
{
	uint a, b, c;

	void Mix()
	{
		a -= b; a -= c; a ^= (c>>13); 
		b -= c; b -= a; b ^= (a<<8); 
		c -= a; c -= b; c ^= (b>>13); 
		a -= b; a -= c; a ^= (c>>12);  
		b -= c; b -= a; b ^= (a<<16); 
		c -= a; c -= b; c ^= (b>>5); 
		a -= b; a -= c; a ^= (c>>3);  
		b -= c; b -= a; b ^= (a<<10); 
		c -= a; c -= b; c ^= (b>>15); 
	}

	public override uint ComputeHash(byte[] data)
	{
		int len = data.Length;
		a = b = 0x9e3779b9;
		c = 0;
		int i = 0;
		while (i + 12 <= len)
		{
			a += (uint)data[i++] |
				((uint)data[i++] << 8) |
				((uint)data[i++] << 16) |
				((uint)data[i++] << 24);
			b += (uint)data[i++] |
				((uint)data[i++] << 8) |
				((uint)data[i++] << 16) |
				((uint)data[i++] << 24);
			c += (uint)data[i++] |
				((uint)data[i++] << 8) |
				((uint)data[i++] << 16) |
				((uint)data[i++] << 24);
			Mix();
		}
		c += (uint) len;
		if (i < len)
			a += data[i++];
		if (i < len)
			a += (uint)data[i++] << 8;
		if (i < len)
			a += (uint)data[i++] << 16;
		if (i < len)
			a += (uint)data[i++] << 24;
		if (i < len)
			b += (uint)data[i++];
		if (i < len)
			b += (uint)data[i++] << 8;
		if (i < len)
			b += (uint)data[i++] << 16;
		if (i < len)
			b += (uint)data[i++] << 24;
		if (i < len)
			c += (uint)data[i++] << 8;
		if (i < len)
			c += (uint)data[i++] << 16;
		if (i < len)
			c += (uint)data[i++] << 24;
		Mix();
		return c;
	}
}

public class Jenkins32 : HashFunction
{
	uint key;

	void Mix()
	{
		key += (key << 12);
		key ^= (key >> 22);
		key += (key << 4);
		key ^= (key >> 9);
		key += (key << 10);
		key ^= (key >> 2);
		key += (key << 7);
		key ^= (key >> 12);
	}

	public override uint ComputeHash(byte[] data)
	{
		key = 1;
		foreach (byte b in data)
		{
			key += b;
			Mix();
		}
		return key;
	}
}

public class SHA1Hash : HashFunction
{
	SHA1 sha = SHA1.Create();

	public override uint ComputeHash(byte[] data)
	{
		byte[] hash = sha.ComputeHash(data);
		return BitConverter.ToUInt32(hash, 0);
	}
}


public class MD : HashFunction
{
	MD5 md5 = MD5.Create();

	public override uint ComputeHash(byte[] data)
	{
		byte[] hash = md5.ComputeHash(data);
		return BitConverter.ToUInt32(hash, 0);
	}
}

public class Cheater : HashFunction
{
	public override uint ComputeHash(byte[] data)
	{
		byte[] b = new byte[4];
		int i = 0;
		while (i < 4 && i < data.Length)
		{
			b[i] ^= data[i];
			i++;
		}
		while (i < 4)
		{
			b[i] ^= data[i % data.Length];
			i++;
		}
		return BitConverter.ToUInt32(b, 0);
	}
}

public class JenkinsOneAtATime : HashFunction
{
	public override uint ComputeHash(byte[] data)
	{
		uint hash = 0;
		foreach (byte b in data)
		{
			hash += b;
			hash += (hash << 10);	// 10
			hash ^= (hash >> 6);	// 6
		}
		hash += (hash << 3);	// 3
		hash ^= (hash >> 11);	// 11
		hash += (hash << 15);	// 15
		return hash;
	}
}

public class FletcherChecksum : HashFunction
{
	public override uint ComputeHash(byte[] data)
	{
		uint hash = 0;
		uint sum = 0;
		foreach (byte b in data)
		{
			sum += b;
			hash += sum;
		}
		return hash;
	}
}

public class CRC32 : HashFunction
{
	uint[] tab;

	public CRC32()
	{
		Init(0x04c11db7);
	}

	public CRC32(uint poly)
	{
		Init(poly);
	}

	void Init(uint poly)
	{
		tab = new uint[256];
		for (uint i=0; i<256; i++)
		{
			uint t = i;
			for (int j=0; j<8; j++)
				if ((t & 1) == 0)
					t >>= 1;
				else
					t = (t >> 1) ^ poly;
			tab[i] = t;
		}
	}

	public override uint ComputeHash(byte[] data)
	{
		uint hash = 0xFFFFFFFF;
		foreach (byte b in data)
			hash = (hash << 8) ^ tab[b ^ (hash >> 24)];
		return ~hash;
	}
}

public class SBoxHash : HashFunction
{
    uint[] sbox = new uint[] {
        0xF53E1837, 0x5F14C86B, 0x9EE3964C, 0xFA796D53,
        0x32223FC3, 0x4D82BC98, 0xA0C7FA62, 0x63E2C982,
        0x24994A5B, 0x1ECE7BEE, 0x292B38EF, 0xD5CD4E56,
        0x514F4303, 0x7BE12B83, 0x7192F195, 0x82DC7300,
        0x084380B4, 0x480B55D3, 0x5F430471, 0x13F75991,
        0x3F9CF22C, 0x2FE0907A, 0xFD8E1E69, 0x7B1D5DE8,
        0xD575A85C, 0xAD01C50A, 0x7EE00737, 0x3CE981E8,
        0x0E447EFA, 0x23089DD6, 0xB59F149F, 0x13600EC7,
        0xE802C8E6, 0x670921E4, 0x7207EFF0, 0xE74761B0,
        0x69035234, 0xBFA40F19, 0xF63651A0, 0x29E64C26,
        0x1F98CCA7, 0xD957007E, 0xE71DDC75, 0x3E729595,
        0x7580B7CC, 0xD7FAF60B, 0x92484323, 0xA44113EB,
        0xE4CBDE08, 0x346827C9, 0x3CF32AFA, 0x0B29BCF1,
        0x6E29F7DF, 0xB01E71CB, 0x3BFBC0D1, 0x62EDC5B8,
        0xB7DE789A, 0xA4748EC9, 0xE17A4C4F, 0x67E5BD03,
        0xF3B33D1A, 0x97D8D3E9, 0x09121BC0, 0x347B2D2C,
        0x79A1913C, 0x504172DE, 0x7F1F8483, 0x13AC3CF6,
        0x7A2094DB, 0xC778FA12, 0xADF7469F, 0x21786B7B,
        0x71A445D0, 0xA8896C1B, 0x656F62FB, 0x83A059B3,
        0x972DFE6E, 0x4122000C, 0x97D9DA19, 0x17D5947B,
        0xB1AFFD0C, 0x6EF83B97, 0xAF7F780B, 0x4613138A,
        0x7C3E73A6, 0xCF15E03D, 0x41576322, 0x672DF292,
        0xB658588D, 0x33EBEFA9, 0x938CBF06, 0x06B67381,
        0x07F192C6, 0x2BDA5855, 0x348EE0E8, 0x19DBB6E3,
        0x3222184B, 0xB69D5DBA, 0x7E760B88, 0xAF4D8154,
        0x007A51AD, 0x35112500, 0xC9CD2D7D, 0x4F4FB761,
        0x694772E3, 0x694C8351, 0x4A7E3AF5, 0x67D65CE1,
        0x9287DE92, 0x2518DB3C, 0x8CB4EC06, 0xD154D38F,
        0xE19A26BB, 0x295EE439, 0xC50A1104, 0x2153C6A7,
        0x82366656, 0x0713BC2F, 0x6462215A, 0x21D9BFCE,
        0xBA8EACE6, 0xAE2DF4C1, 0x2A8D5E80, 0x3F7E52D1,
        0x29359399, 0xFEA1D19C, 0x18879313, 0x455AFA81,
        0xFADFE838, 0x62609838, 0xD1028839, 0x0736E92F,
        0x3BCA22A3, 0x1485B08A, 0x2DA7900B, 0x852C156D,
        0xE8F24803, 0x00078472, 0x13F0D332, 0x2ACFD0CF,
        0x5F747F5C, 0x87BB1E2F, 0xA7EFCB63, 0x23F432F0,
        0xE6CE7C5C, 0x1F954EF6, 0xB609C91B, 0x3B4571BF,
        0xEED17DC0, 0xE556CDA0, 0xA7846A8D, 0xFF105F94,
        0x52B7CCDE, 0x0E33E801, 0x664455EA, 0xF2C70414,
        0x73E7B486, 0x8F830661, 0x8B59E826, 0xBB8AEDCA,
        0xF3D70AB9, 0xD739F2B9, 0x4A04C34A, 0x88D0F089,
        0xE02191A2, 0xD89D9C78, 0x192C2749, 0xFC43A78F,
        0x0AAC88CB, 0x9438D42D, 0x9E280F7A, 0x36063802,
        0x38E8D018, 0x1C42A9CB, 0x92AAFF6C, 0xA24820C5,
        0x007F077F, 0xCE5BC543, 0x69668D58, 0x10D6FF74,
        0xBE00F621, 0x21300BBE, 0x2E9E8F46, 0x5ACEA629,
        0xFA1F86C7, 0x52F206B8, 0x3EDF1A75, 0x6DA8D843,
        0xCF719928, 0x73E3891F, 0xB4B95DD6, 0xB2A42D27,
        0xEDA20BBF, 0x1A58DBDF, 0xA449AD03, 0x6DDEF22B,
        0x900531E6, 0x3D3BFF35, 0x5B24ABA2, 0x472B3E4C,
        0x387F2D75, 0x4D8DBA36, 0x71CB5641, 0xE3473F3F,
        0xF6CD4B7F, 0xBF7D1428, 0x344B64D0, 0xC5CDFCB6,
        0xFE2E0182, 0x2C37A673, 0xDE4EB7A3, 0x63FDC933,
        0x01DC4063, 0x611F3571, 0xD167BFAF, 0x4496596F,
        0x3DEE0689, 0xD8704910, 0x7052A114, 0x068C9EC5,
        0x75D0E766, 0x4D54CC20, 0xB44ECDE2, 0x4ABC653E,
        0x2C550A21, 0x1A52C0DB, 0xCFED03D0, 0x119BAFE2,
        0x876A6133, 0xBC232088, 0x435BA1B2, 0xAE99BBFA,
        0xBB4F08E4, 0xA62B5F49, 0x1DA4B695, 0x336B84DE,
        0xDC813D31, 0x00C134FB, 0x397A98E6, 0x151F0E64,
        0xD9EB3E69, 0xD3C7DF60, 0xD2F2C336, 0x2DDD067B,
        0xBD122835, 0xB0B3BD3A, 0xB0D54E46, 0x8641F1E4,
        0xA0B38F96, 0x51D39199, 0x37A6AD75, 0xDF84EE41,
        0x3C034CBA, 0xACDA62FC, 0x11923B8B, 0x45EF170A,	
	};

    public override uint ComputeHash(byte[] data)
    {
        uint hash = 0;
        foreach (byte b in data)
        {
            hash ^= sbox[b];
            hash *= 3;
        }
        return hash;
    }
}

/* From: src/kern/include/nzat.h,v 1.2 2011/07/18 00:35:40 tg Exp $ */

public class NZAATHash : HashFunction
{
	public override uint ComputeHash(byte[] data)
	{
		uint hash = 0;
		foreach (byte b in data)
		{
			hash += b;
			++hash;
			hash += (hash << 10);	// 10
			hash ^= (hash >> 6);	// 6
		}
		hash += (hash << 10);	// 10
		hash ^= (hash >> 6);	// 6
		hash += (hash << 3);	// 3
		hash ^= (hash >> 11);	// 11
		hash += (hash << 15);	// 15
		return hash;
	}
}

public class NZATHash : HashFunction
{
	public override uint ComputeHash(byte[] data)
	{
		uint hash = 0;
		foreach (byte b in data)
		{
			hash += b;
			++hash;
			hash += (hash << 10);	// 10
			hash ^= (hash >> 6);	// 6
		}
		if (hash == 0)
			return 1;
		hash += (hash << 10);	// 10
		hash ^= (hash >> 6);	// 6
		hash += (hash << 3);	// 3
		hash ^= (hash >> 11);	// 11
		hash += (hash << 15);	// 15
		return hash;
	}
}
