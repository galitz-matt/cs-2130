def main():
	n0, n1 = 1, 1
	i = 0
	while i - 65 <= 0:
		print(n0)
		nth = n0 + n1
		n0 = n1
		n1 = nth
		i += 1

if __name__ == "__main__":
	main()