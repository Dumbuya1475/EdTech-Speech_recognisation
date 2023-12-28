# NUM = 5
# CAL = NUM / 3
# REM = NUM % 3
# NU = NUM // 3
# print(CAL)
# print(f"{NU} Remainder {REM}")
# # print(f"Remainder {REM}")

# Print alphabet from 'a' to 'z'
print("Alphabet from 'a' to 'z':")
for char in range(ord('a'), ord('z') + 1):
    print(chr(char), end=' ')
print()  # Move to the next line

# Print alphabet in reverse order
print("Alphabet in reverse order:")
for char in range(ord('z'), ord('a') - 1, -1):
    print(chr(char), end=' ')
print()  # Move to the next line

# Print alphabet from 'a' to 'z'
print("Alphabet from 'a' to 'z':")
for char_code in range(ord('a'), ord('z') + 1):
    print(chr(char_code), end=' ')
print()  # Move to the next line

# Print alphabet in reverse order
print("Alphabet in reverse order:")
for char_code in range(ord('z'), ord('a') - 1, -1):
    print(chr(char_code), end=' ')
print()  # Move to the next line

print("This is a line.", end=' ///')
print("This is another line.")
