import 'package:flutter/material.dart';

class TextWidget extends StatelessWidget {
  final String data;
  const TextWidget(this.data, {super.key});

  @override
  Widget build(context) {
    return Text(
      data,
      style: const TextStyle(
        fontSize: 18,
        color: Colors.white,
      ),
    );
  }
}
