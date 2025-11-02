import argparse

def config_to_header(input_file, output_file):
    with open(input_file, "r") as infile, open(output_file, "w") as outfile:
        for line in infile:
            line = line.strip()

            # Skip empty lines and comments
            if not line or line.startswith("#"):
                continue

            if line.startswith("CONFIG_"):
                config_line = line[len("CONFIG_"):]

                if config_line.endswith("=y"):
                    name = config_line[:-2]
                    outfile.write(f"#define {name}\n")

                elif config_line.endswith("=n"):
                    name = config_line[:-2]
                    outfile.write(f"#undef {name}\n")

                elif "=" in config_line:
                    name, value = config_line.split("=", 1)
                    outfile.write(f"#define {name} {value}\n")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Convert text config file into C header file"
    )
    parser.add_argument("input", help="path to config text file")
    parser.add_argument("output", help="path to generate output header")

    args = parser.parse_args()
    config_to_header(args.input, args.output)
    print(f"Generated config.h: {args.input} → {args.output}")

