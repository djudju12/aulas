import 'package:flutter/material.dart';
import 'package:google_fonts/google_fonts.dart';

class TitleText extends StatelessWidget {
  final String data;
  const TitleText(this.data, {super.key});

  @override
  Widget build(context) {
    return Text(
      data,
      style: GoogleFonts.lato(
        color: const Color.fromARGB(255, 189, 121, 221),
        fontSize: 20,
        fontWeight: FontWeight.bold,
      ),
      textAlign: TextAlign.center,
    );
  }
}
