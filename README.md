# NanoTekSpice

Simulator of logic circuits and digital electronics.

```
$ ./nanotekspice [circuit file]
```

## Example of circuit

```nts
.chipsets:
input a
input b
4071 or
output s
.links:
a:1 or:1
b:1 or:2
or:3 s:1
```

### Format

```nts
.chipsets:
[chip type] [chip name]  # [comment]
[chip type] [chip name]
...

.links:
[chip name]:[pin number] [chip name]:[pin number]
[chip name]:[pin number] [chip name]:[pin number]
...
```


## Score

Weighted average score in all categories: 72.1%

| Category                 | Score |
|--------------------------|-------|
| Components and tests     | 65%   |
| Parsing                  | 100%  |
| Rigor                    | 100%  |

## Components done
| Component                      | Passed |
| ------------------------------ | -----  |
| Input (input)                  | Yes    |
| Output (output)                | Yes    |
| Clock (clock)                  | Yes    |
| And (4081)                     | Yes    |
| Or  (4071)                     | Yes    |
| Not (4069)                     | Yes    |
| Nand (4011)                    | Yes    |
| Nor (4001)                     | Yes    |
| Xor (4030)                     | Yes    |
| 4bit Adder (4040)              | Yes    |
| Flip Flop (4013)               | No     |
| Logger (logger)                | No     |

## Components not done
| Components                     |
|--------------------------------|
| Decoder (4514)                 |
| Decade Counter (4040)          |
| Johnson (4017)                 |
| 8bits Shift Register (4094)    |
| 8 Channel Data Selector (4512) |
| RAM (4801)                     |
| ROM (2716)                     |
